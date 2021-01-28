#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "GraphObject.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

/////////////////////////////
// Prototypes
/////////////////////////////
class Actor;
class Socrates;

class StudentWorld : public GameWorld {
public:
    // Constructor/Destructor
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    
    // Virtual Functions
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // Mutator
    void addActor(Actor* newActor); // allows actors to be added to the world
    
    // Utility Functions
    bool checkHit(double x, double y, int damage); // checks a projectile hit
    bool eatFood(double x, double y); // processes a bacteria eating food, returns true if it does
    bool blocked(double x, double y); // checks if bacteria are in contact w dirt or the border, returns 0 if not blocked, 1 if blocked by dirt, 2 if blocked by border
    bool findFood(double x, double y, Direction& dir); // checks if theres food in a 72 pix radius
    int findSocrates(double x, double y, Direction& dir); // returns how far away socrates is/direction hes in
    
    // Player Modifiers
    void restoreHealth() const; // restores socrates to full health
    void restoreFlames() const; // adds 5 flame charges
    void doDamage(int damage) const; // does damage
private:
    Socrates* m_player;
    std::list<Actor*> m_actors;
    
    double distBetween(double x1, double y1, double x2, double y2) const; // returns distance
    void generateRandPos(double& x, double& y) const; // generates random goodie spawn locations
    bool generateInitPos(double& x, double& y); // generates positions for pits/food/dirt, returns false if overlap occurs when it shouldnt
    Direction getDirTowards(double x1, double y1, double x2, double y2) const; // gets direction from pos1 to pos2
};

#endif // STUDENTWORLD_H_


// TO DO
// Fix agg salmonella getting stuck on border
// Comment/organize all code
// Check sounds
// End level after clearing pits
