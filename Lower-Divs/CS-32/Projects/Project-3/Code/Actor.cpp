#include "Actor.h"
#include "GameConstants.h"
#include "StudentWorld.h"
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
/////////////////////////////
// Base Class
/////////////////////////////

// Constructor/Destructor
Actor::Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world) : GraphObject(imageID, startX, startY, dir, depth), m_dead(false), m_world(world) {}

Actor::~Actor() {}

// Virtual Functions
bool Actor::blocksSpawns() const { return false; }

bool Actor::isDamageable() const { return true; }

bool Actor::isFood() const { return false; }

bool Actor::isDirt() const { return false; }

bool Actor::isEnemy() const { return false; }

void Actor::takeDamage(int damage) { setDead(); }

// Mutators/Accessors
bool Actor::getDead() const { return m_dead; }

void Actor::setDead() { m_dead = true; }

StudentWorld* Actor::getWorld() const { return m_world; }

/////////////////////////////
// Socrates
/////////////////////////////

// Constructor/Destructor
Socrates::Socrates(StudentWorld* world) : Actor(IID_PLAYER, 0, VIEW_HEIGHT / 2, 0, 0, world), m_health(100), m_flameAmmo(5), m_sprayAmmo(20) {}

Socrates::~Socrates() {};

// Virtual Functions
void Socrates::doSomething() {
    if (getDead()) return;
    int key;
    if (getWorld()->getKey(key)) {
        switch(key) {
            case KEY_PRESS_LEFT: { // movement counterclockwise
                setDirection(getDirection() + 5);
                move5Degrees();
                break;
            }
            case KEY_PRESS_RIGHT: { // movement clockwise
                setDirection(getDirection() - 5);
                move5Degrees();
                break;
            }
            case KEY_PRESS_SPACE: // spray attack
                if (m_sprayAmmo >= 1) {
                    getWorld()->playSound(SOUND_PLAYER_SPRAY);
                    double x, y;
                    getPositionInThisDirection(getDirection(), SPRITE_WIDTH, x, y);
                    Spray* newSpray = new Spray(x, y, getDirection(), getWorld());
                    getWorld()->addActor(newSpray);
                    m_sprayAmmo--;
                }
                break;
            case KEY_PRESS_ENTER: // flamethrower
                if (m_flameAmmo >= 1) {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    for (int i = 0; i < 16; i++) { // set 16 charges
                        double x, y;
                        getPositionInThisDirection(i * 22, SPRITE_WIDTH, x, y);
                        Flame* flame = new Flame(x, y, i * 22, getWorld());
                        getWorld()->addActor(flame);
                    }
                    m_flameAmmo--;
                }
        }
    } else {
        if (m_sprayAmmo < 20) m_sprayAmmo++; // regen spray ammo
    }
}

void Socrates::takeDamage(int damage) {
    if (m_health - damage <= 0) m_health = 0; // health cant be negative
    else m_health -= damage;
    if (m_health == 0) {
        setDead();
        getWorld()->decLives();
    }
}

// Accessors for Display
int Socrates::getHealth() const { return m_health; }

int Socrates::getSprays() const { return m_sprayAmmo; }

int Socrates::getFlames() const { return m_flameAmmo; }

// Mutators for Goodies
void Socrates::heal() { m_health = 100; }

void Socrates::regenFlames() { m_flameAmmo += 5; }

// Private Function
void Socrates::move5Degrees() {
    const double PI = 4 * atan(1);
    double x = VIEW_RADIUS - cos(getDirection() * 2 * PI / 360) * VIEW_RADIUS;
    double y = VIEW_RADIUS - sin(getDirection() * 2 * PI / 360) * VIEW_RADIUS;
    moveTo(x, y);
}

/////////////////////////////
// Dirt
/////////////////////////////

// Constructor/Destructor
DirtPile::DirtPile(double x, double y, StudentWorld* world) : Actor(IID_DIRT, x, y, 0, 1, world) {}

DirtPile::~DirtPile() {}

// Virtual Functions
void DirtPile::doSomething() {}

bool DirtPile::isDirt() const { return true; }

/////////////////////////////
// Food
/////////////////////////////

// Constructor/Destructor
Food::Food(double x, double y, StudentWorld* world) : Actor(IID_FOOD, x, y, 90, 1, world) {}

Food::~Food() {}

// Virtual Functions
void Food::doSomething() {}

bool Food::blocksSpawns() const { return true; }

bool Food::isDamageable() const { return false; }

bool Food::isFood() const { return true; }

/////////////////////////////
// Projectile
/////////////////////////////

// Constructor/Destructor
Projectile::Projectile(int ID, double x, double y, Direction dir, int maxDist, int damage, StudentWorld* world) : Actor(ID, x, y, dir, 1, world), m_maxDist(maxDist), m_distTraveled(0), m_damage(damage) {}

Projectile::~Projectile() {}

// Virtual Functions
void Projectile::doSomething() {
    if (getDead()) return;
    if (getWorld()->checkHit(getX(), getY(), m_damage)) { // only hits one thing
        setDead();
        return;
    }
    m_distTraveled += SPRITE_WIDTH; // projectile travels forward
    double x; double y;
    getPositionInThisDirection(getDirection(), SPRITE_WIDTH, x, y);
    moveTo(x, y);
    if (m_distTraveled > m_maxDist) setDead();
}

bool Projectile::isDamageable() const { return false; }

/////////////////////////////
// Flames
/////////////////////////////

// Constructors/Destructors
Flame::Flame(double x, double y, Direction dir, StudentWorld* world) : Projectile(IID_FLAME, x, y, dir, 32, 5, world) {}

Flame::~Flame() {}

/////////////////////////////
// Spray
/////////////////////////////

// Constructors/Destructors
Spray::Spray(double x, double y, Direction dir, StudentWorld* world) : Projectile(IID_SPRAY, x, y, dir, 112, 2, world) {}

Spray::~Spray() {}

/////////////////////////////
// Goodies
/////////////////////////////

// Constructors/Destructors
Goodies::Goodies(int ID, double x, double y, StudentWorld* world, int lifetime) : Actor(ID, x, y, 0, 1, world),  m_lifetime(lifetime) {}

Goodies::~Goodies() {}

// Virtual Function
void Goodies::doSomething() {
    if (getDead()) return;
    Direction trash;
    if (getWorld()->findSocrates(getX(), getY(), trash) <= SPRITE_WIDTH) {
        setDead();
        doEffect();
    }
    m_lifetime--;
    if (m_lifetime <= 0) setDead();
}

/////////////////////////////
// HealthKit
/////////////////////////////

// Constructors/Destructors
HealthKit::HealthKit(double x, double y, StudentWorld* world, int lifespan) : Goodies(IID_RESTORE_HEALTH_GOODIE, x, y, world, lifespan) {}

HealthKit::~HealthKit() {}

// Virtual Function
void HealthKit::doEffect() {
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->restoreHealth();
    getWorld()->increaseScore(250);
}

/////////////////////////////
// FlameCharge
/////////////////////////////

// Constructors/Destructors
FlameCharge::FlameCharge(double x, double y, StudentWorld* world, int lifespan) : Goodies(IID_FLAME_THROWER_GOODIE, x, y, world, lifespan) {}

FlameCharge::~FlameCharge() {}

// Virtual Function
void FlameCharge::doEffect() {
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->restoreFlames();
    getWorld()->increaseScore(300);
}

/////////////////////////////
// ExtraLife
/////////////////////////////

// Constructors/Destructors
ExtraLife::ExtraLife(double x, double y, StudentWorld* world, int lifespan) : Goodies(IID_EXTRA_LIFE_GOODIE, x, y, world, lifespan) {}

ExtraLife::~ExtraLife() {}

// Virtual Function
void ExtraLife::doEffect() {
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->incLives();
    getWorld()->increaseScore(500);
}

/////////////////////////////
// Fungus
/////////////////////////////

// Constructors/Destructors
Fungus::Fungus(double x, double y, StudentWorld* world, int lifespan) : Goodies(IID_FUNGUS, x, y, world, lifespan) {}

Fungus::~Fungus() {}

// Virtual Function
void Fungus::doEffect() {
    getWorld()->doDamage(20);
    if (getWorld()->getScore() - 50 < 0) getWorld()->increaseScore(-1 * getWorld()->getScore());
    else getWorld()->increaseScore(-50);
}

/////////////////////////////
// Pit
/////////////////////////////

// Constructors/Destructors
Pit::Pit(double x, double y, StudentWorld* world) : Actor(IID_PIT, x, y, 0, 1, world), m_numAggSalmonella(3), m_numSalmonella(5), m_numEColi(2) {}

Pit::~Pit() {}

// Virtual Function
void Pit::doSomething() {
    if (m_numEColi + m_numSalmonella + m_numAggSalmonella <= 0) { // if all bacteria emitted
        setDead();
        return;
    }
    if (randInt(1, 50) == 1) { // 1/50 chance
        bool spawnReady = true;
        while (spawnReady) {
            switch (randInt(1, 3)) { // equal chance for all 3 types
                case 1: { // spawn salmonella
                    if (m_numSalmonella > 0) {
                        Salmonella* newBact = new Salmonella(getX(), getY(), getWorld());
                        getWorld()->addActor(newBact);
                        m_numSalmonella--; spawnReady = false;
                        break;
                    } else continue; // if out of this bacteria, retry
                }
                case 2: { // spawn agg. salmonella
                    if (m_numAggSalmonella > 0) {
                        AggSalmonella* newBact = new AggSalmonella(getX(), getY(), getWorld());
                        getWorld()->addActor(newBact);
                        m_numAggSalmonella--; spawnReady = false;
                        break;
                    } else continue;
                }
                case 3: { // spawn e coli
                    if (m_numEColi > 0) {
                        EColi* newBact = new EColi(getX(), getY(), getWorld());
                        getWorld()->addActor(newBact);
                        m_numEColi--; spawnReady = false;
                        break;
                    } else continue;
                }
            }
        }
        getWorld()->playSound(SOUND_BACTERIUM_BORN);
    }
}

bool Pit::blocksSpawns() const { return true; }

bool Pit::isDamageable() const { return false; }

bool Pit::isEnemy() const { return true; }

/////////////////////////////
// Bacteria
/////////////////////////////

// Constructor/Destructor
Bacteria::Bacteria(int ID, double x, double y, int health, StudentWorld* world) : Actor(ID, x, y, 90, 0, world), m_health(health), m_mpd(0), m_foodEaten(0) {}

Bacteria::~Bacteria() {}

// Virtual Functions
bool Bacteria::isEnemy() const { return true; }

void Bacteria::takeDamage(int damage) {
    m_health -= damage;
    if (m_health <= 0) {
        if (randInt(1, 2) == 1) { // 50% chance to turn into food
            Food* food = new Food(getX(), getY(), getWorld());
            getWorld()->addActor(food);
        }
        setDead();
        if (isEColi()) getWorld()->playSound(SOUND_ECOLI_DIE);
        else getWorld()->playSound(SOUND_SALMONELLA_DIE);
        getWorld()->increaseScore(100);
    } else {
        if (isEColi()) getWorld()->playSound(SOUND_ECOLI_HURT);
        else getWorld()->playSound(SOUND_SALMONELLA_HURT);
    }
}

bool Bacteria::isEColi() const { return false; }

// Mutator
void Bacteria::ateFood() { m_foodEaten++; }

// Other Functions
bool Bacteria::duplicate(double& newX, double& newY) {
    if (m_foodEaten >= 3) {
        newX = getX(); newY = getY(); // set new coords equal to own
        if (getX() < VIEW_WIDTH / 2) newX = getX() + SPRITE_WIDTH / 2; // add sprite width / 2 if x less than view width / 2
        else if (getX() > VIEW_WIDTH / 2) newX = getX() - SPRITE_WIDTH / 2; // subtract sprite width / 2 if x greater than view width / 2
        if (getY() < VIEW_HEIGHT / 2) newY = getY() + SPRITE_WIDTH / 2;
        else if (getY() > VIEW_HEIGHT / 2) newY = getY() - SPRITE_WIDTH / 2;
        m_foodEaten = 0;
        return true;
    } else return false;
}

void Bacteria::adjustForMPD() {
    if (m_mpd > 0) { // step 5
        m_mpd--;
        double newX; double newY;
        getPositionInThisDirection(getDirection(), 3, newX, newY);
        if (!getWorld()->blocked(newX, newY)) moveTo(newX, newY);
        else {
            setDirection(randInt(0, 359));
            m_mpd = 10;
            return;
        }
    } else { // step 6
        Direction temp; // only used if food found
        if (!getWorld()->findFood(getX(), getY(), temp)) {
            setDirection(randInt(0, 359));
            m_mpd = 10;
            return;
        } else {
            setDirection(temp); // points in dir of closest food
            m_mpd = 10;
        }
    }
}

/////////////////////////////
// Salmonella
/////////////////////////////

// Constructor/Destructor
Salmonella::Salmonella(double x, double y, StudentWorld* world) : Bacteria(IID_SALMONELLA, x, y, 4, world) {}

Salmonella::~Salmonella() {}

// Virtual Function
void Salmonella::doSomething() {
    if (getDead()) return;
    Direction trash;
    if (getWorld()->findSocrates(getX(), getY(), trash) <= SPRITE_RADIUS) { // step 2
        getWorld()->doDamage(1);
    } else { // step 3 (skipped if step 2 happens)
        double x, y;
        if (duplicate(x, y)) {
            Salmonella* s = new Salmonella(x, y, getWorld());
            getWorld()->addActor(s);
        } else { // step 4 (skipped if step 2/3 happen)
            if (getWorld()->eatFood(getX(), getY())) ateFood();
        }
    }
    adjustForMPD(); // step 5/6
}

/////////////////////////////
// AggSalmonella
/////////////////////////////

// Constructor/Destructor
AggSalmonella::AggSalmonella(double x, double y, StudentWorld* world) : Bacteria(IID_SALMONELLA, x, y, 10, world) {}

AggSalmonella::~AggSalmonella() {}

// Virtual Function
void AggSalmonella::doSomething() {
    if (getDead()) return; // step 1
    Direction temp; double newX, newY; bool stop = false;
    if (getWorld()->findSocrates(getX(), getY(), temp) <= 72) { // step 2
        getPositionInThisDirection(temp, 3, newX, newY);
        setDirection(temp);
        if (!getWorld()->blocked(newX, newY)) moveTo(newX, newY); // incomplete, need to fix if stuck on border
        stop = true; // stops before step 6
    }
    Direction trash;
    if (getWorld()->findSocrates(getX(), getY(), trash) <= SPRITE_RADIUS) { // step 3
        getWorld()->doDamage(2);
    } else { // step 4
        double x, y;
        if (duplicate(x, y)) {
            AggSalmonella* as = new AggSalmonella(x, y, getWorld());
            getWorld()->addActor(as);
        } else { // step 5
            if (getWorld()->eatFood(getX(), getY())) ateFood();
        }
    }
    if (stop) return;
    adjustForMPD();
}

/////////////////////////////
// EColi
/////////////////////////////

// Constructor/Destructor
EColi::EColi(double x, double y, StudentWorld* world) : Bacteria(IID_ECOLI, x, y, 5, world) {}

EColi::~EColi() {}

// Virtual Functions
void EColi::doSomething() {
    if (getDead()) return;
    Direction temp; double newX, newY;
    Direction trash;
    if (getWorld()->findSocrates(getX(), getY(), trash) <= SPRITE_RADIUS) { // step 2
    getWorld()->doDamage(4);
    } else {
        double x, y;
        if (duplicate(x, y)) {
            EColi* e = new EColi(x, y, getWorld());
            getWorld()->addActor(e);
        } else {
            if (getWorld()->eatFood(getX(), getY())) ateFood();
        }
    }
    if (getWorld()->findSocrates(getX(), getY(), temp) <= 256) {
        for (int i = 0; i < 10; i++) {
            getPositionInThisDirection(temp, 2, newX, newY);
            if (!getWorld()->blocked(newX, newY)) {
                moveTo(newX, newY);
                return;
            } else {
                temp += 10;
                setDirection(temp);
            }
        }
    }
}

bool EColi::isEColi() const { return true; }
