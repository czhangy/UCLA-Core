#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

GameWorld* createStudentWorld(string assetPath) { return new StudentWorld(assetPath); }

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

// Constructor/Destructor
StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath) {}

StudentWorld::~StudentWorld() { cleanUp(); }

// Virtual Functions
int StudentWorld::init() {
    m_player = new Socrates(this);
    int i = 0, j = 0, k = 0;
    while (i < getLevel()) { // make pits
        double x, y;
        if (!generateInitPos(x, y)) continue; // check for overlap w pits
        Pit* pit = new Pit(x, y, this);
        m_actors.push_back(pit);
        i++;
    }
    while (j < min(5 * getLevel(), 25)) { // make food
        double x, y;
        if (!generateInitPos(x, y)) continue; // check for overlap w pits
        Food* food = new Food(x, y, this);
        m_actors.push_back(food);
        j++;
    }
    while (k < max(180 - 20 * getLevel(), 20)) { // make dirt
        double x, y;
        if (!generateInitPos(x, y)) continue; // check for overlap w pits and food
        DirtPile* dirt = new DirtPile(x, y, this);
        m_actors.push_back(dirt);
        k++;
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    m_player->doSomething();
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) { // make everything do something
        if (!(*iter)->getDead()) (*iter)->doSomething();
        if (m_player->getDead()) return GWSTATUS_PLAYER_DIED; // if Socrates dies
    }
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end();) { // deletes dead objects
        if ((*iter)->getDead()) {
            Actor* temp = *iter;
            iter = m_actors.erase(iter);
            delete temp;
        } else iter++;
    }
    int chanceFungus = max(510 - getLevel() * 10, 200), chanceGoodie = max(510 - getLevel() * 10, 250);
    double x; double y;
    if (randInt(0, chanceFungus - 1) == 0) {
        generateRandPos(x, y);
        Fungus* newFungus = new Fungus(x, y, this, max(randInt(0, 300 - 10 * getLevel() - 1), 50));
        m_actors.push_front(newFungus);
    }
    if (randInt(0, chanceGoodie - 1) == 0) {
        generateRandPos(x, y);
        int rand = randInt(1, 10);
        if (rand == 10) { // 10% chance
            ExtraLife* newGoodie = new ExtraLife(x, y, this, max(randInt(0, 300 - 10 * getLevel() - 1), 50));
            m_actors.push_front(newGoodie);
        } else if (rand > 6) { // 30% chance
            FlameCharge* newGoodie = new FlameCharge(x, y, this, max(randInt(0, 300 - 10 * getLevel() - 1), 50));
            m_actors.push_front(newGoodie);
        } else { // 60% chance
            HealthKit* newGoodie = new HealthKit(x, y, this, max(randInt(0, 300 - 10 * getLevel() - 1), 50));
            m_actors.push_back(newGoodie);
        }
    }
    
    ostringstream score; ostringstream level; ostringstream lives; ostringstream health; ostringstream spray; ostringstream flame; // set up display
    score.fill('0');
    score << setw(6) << getScore(); level << getLevel(); lives << getLives(); health << m_player->getHealth(); spray << m_player->getSprays(); flame << m_player->getFlames();
    setGameStatText("Score: " + score.str() + "  Level: " + level.str() + "  Lives: " + lives.str() + "  Health: " + health.str() + "  Sprays: " + spray.str() + "  Flames: " + flame.str());
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if ((*iter)->isEnemy()) return GWSTATUS_CONTINUE_GAME;
    }
    return GWSTATUS_FINISHED_LEVEL;
}

void StudentWorld::cleanUp() {
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end();) {
        Actor* temp = *iter;
        iter = m_actors.erase(iter);
        delete temp;
    }
    if (m_player != nullptr) {
        delete m_player;
        m_player = nullptr; // catches if cleanUp() tries to run twice
    }
}

// Mutator
void StudentWorld::addActor(Actor* newActor) { m_actors.push_front(newActor); }

// Utility Functions
bool StudentWorld::checkHit(double x, double y, int damage) { // checks for objects hit by projectiles
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if ((*iter)->isDamageable() && distBetween(x, y, (*iter)->getX(), (*iter)->getY()) <= SPRITE_WIDTH) {
            (*iter)->takeDamage(damage);
            return true;
        }
    }
    return false;
}

bool StudentWorld::eatFood(double x, double y) { // eats food if overlap
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if ((*iter)->isFood() && (distBetween(x, y, (*iter)->getX(), (*iter)->getY()) <= SPRITE_WIDTH)) { // check overlap w food
            Actor* ptr = *iter;
            iter = m_actors.erase(iter); // eats food
            delete ptr;
            return true;
        }
    }
    return false;
}

bool StudentWorld::blocked(double x, double y) { // checks to see if bacteria can move forward
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if ((*iter)->isDirt() && distBetween(x, y, (*iter)->getX(), (*iter)->getY()) < SPRITE_WIDTH / 2) return true;
    }
    return (sqrt(pow(x - VIEW_WIDTH / 2, 2) + pow(y - VIEW_HEIGHT / 2, 2)) > VIEW_RADIUS);
}

bool StudentWorld::findFood(double x, double y, Direction& dir) { // checks to see if food is within 128 pix
    int closest = 999; // arbitrary big number
    Actor* nearestFood = nullptr;
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        int temp = distBetween(x, y, (*iter)->getX(), (*iter)->getY());
        if ((*iter)->isFood() && temp <= 128 && temp < closest) { // tracks closest detected food
            closest = temp; nearestFood = *iter;
        }
    }
    if (closest != 999) dir = getDirTowards(x, y, nearestFood->getX(), nearestFood->getY()); // will be initialized, crashes if not
    return closest != 999;
}

int StudentWorld::findSocrates(double x, double y, Direction& dir) { // returns distance to socrates and direction towrds him
    dir = getDirTowards(x, y, m_player->getX(), m_player->getY());
    return distBetween(x, y, m_player->getX(), m_player->getY());
}

// Player Modifiers
void StudentWorld::restoreHealth() const { m_player->heal(); }// restores socrates' health

void StudentWorld::restoreFlames() const { m_player->regenFlames(); } // restores socrates' flames

void StudentWorld::doDamage(int damage) const { m_player->takeDamage(damage); } // damages socrates

/////////////////////////////
// Private Functions
/////////////////////////////

double StudentWorld::distBetween(double x1, double y1, double x2, double y2) const { return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); }

bool StudentWorld::generateInitPos(double& x, double& y) {
    x = randInt(-120, 120);
    y = randInt(-1 * sqrt(pow(120, 2) - pow(x, 2)), sqrt(pow(120, 2) - pow(x, 2))) + VIEW_HEIGHT / 2;
    x += VIEW_WIDTH / 2;
    for (list<Actor*>::iterator iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if ((*iter)->blocksSpawns() && distBetween(x, y, (*iter)->getX(), (*iter)->getY()) < SPRITE_WIDTH) return false; // if contact w food or pit
    }
    return true;
}

void StudentWorld::generateRandPos(double& x, double& y) const {
    x = randInt(-1 * VIEW_RADIUS, VIEW_RADIUS);
    y = sqrt(pow(VIEW_RADIUS, 2) - pow(x, 2));
    if (randInt(1, 2) == 1) { y *= -1; }// 50/50 chance to make y up or down
    x += VIEW_WIDTH / 2;
    y += VIEW_HEIGHT / 2;
}

Direction StudentWorld::getDirTowards(double x1, double y1, double x2, double y2) const {
    double angle = atan((y2 - y1) / (x2 - x1)) * (180 / 4 * atan(1));
    if ((x2 - x1) < 0) angle += 180; // correct for arctan range
    return angle;
}
