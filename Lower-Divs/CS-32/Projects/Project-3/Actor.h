#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"

/////////////////////////////
// Prototypes
/////////////////////////////
class StudentWorld;

/////////////////////////////
// Base Class
/////////////////////////////
class Actor : public GraphObject {
public:
    // Constructor/Destructor
    Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* world);
    virtual ~Actor() = 0;
    
    // Pure Virtual Functions
    virtual void doSomething() = 0; // pure virtual, makes class abstract and forces derived classes to have a doSomething()
    
    // Virtual Functions
    virtual bool blocksSpawns() const; // default virtual returns false, overridden by pits/food to tell world that pits/food/dirt cannot spawn overlapping them
    virtual bool isDamageable() const; // default virtual returns true, overridden by pits/food/projectiles to tell world to ignore these when detecting projectile collision
    virtual bool isFood() const; // default virtual returns false, overridden by food for bacteria detection
    virtual bool isDirt() const; // default virtual returns false, overridden by dirt for bacteria detection
    virtual bool isEnemy() const; // default virtual returns false, overridden by pits/bacteria top allow world to detect if level is over
    virtual void takeDamage(int damage); // default virtual sets object taking damage to dead, overwritten by socrates/bacteria, which have hp, intended unused parameter
    
    // Mutators/Accessors
    bool getDead() const; // returns if the object is dead
    void setDead(); // allows objects to change dead/alive status
    StudentWorld* getWorld() const; // returns a pointer to the world
private:
    bool m_dead; // is the object dead
    StudentWorld* m_world; // contains a pointer to the world the object is in
};

/////////////////////////////
// Socrates
/////////////////////////////
class Socrates : public Actor {
public:
    // Constructor/Destructor
    Socrates(StudentWorld* world);
    ~Socrates();
    
    // Virtual Functions
    virtual void doSomething();
    virtual void takeDamage(int damage); // specialized virtual, decrements health
    
    // Accessors for Display
    int getHealth() const; // returns health, needed for display
    int getSprays() const; // returns spray ammo, needed for display
    int getFlames() const; // returns flame ammo, needed for display
    
    // Mutators for Goodies
    void heal(); // heals socrates to full, needed for when socrates picks up a health kit
    void regenFlames(); // increases flame ammo by 5, needed for when socrates picks up a flame charge
private:
    int m_health; // tracks health
    int m_flameAmmo; // tracks ammo
    int m_sprayAmmo;
    
    void move5Degrees(); // helper method for movement
};

/////////////////////////////
// Dirt
/////////////////////////////
class DirtPile : public Actor {
public:
    // Constructor/Destructor
    DirtPile(double x, double y, StudentWorld* world);
    ~DirtPile();
    
    // Virtual Functions
    virtual void doSomething();
    virtual bool isDirt() const; // specialized virtual, needed for the world to detect when bacteria are overlapping with dirt and cannot move
};

/////////////////////////////
// Food
/////////////////////////////
class Food : public Actor {
public:
    // Constructor/Destructor
    Food(double x, double y, StudentWorld* world);
    ~Food();
    
    // Virtual Functions
    virtual void doSomething();
    virtual bool blocksSpawns() const; // specialized virtual, needed for the world to know food blocks spawning of food/dirt
    virtual bool isDamageable() const; // specialized virtual, needed for the world to know pits cant be damaged
    virtual bool isFood() const; // specialized virtual, needed for the world to detect when bacteria are overlapping with food
};

/////////////////////////////
// Projectiles
/////////////////////////////
class Projectile : public Actor {
public:
    // Constructor/Destructor
    Projectile(int ID, double x, double y, Direction dir, int maxDist, int damage, StudentWorld* world);
    virtual ~Projectile() = 0; // makes class abstract
    
    // Virtual Functions
    virtual void doSomething(); // checks for projectile hit/moves projectiles forward
    virtual bool isDamageable() const; // specialized virtual, needed for the world to know pits cant be damaged
private:
    int m_maxDist; // each projectile type has a different max distance, passed thru constructor
    int m_distTraveled; // each projectile has a varying distance traveled
    int m_damage; // each projectile type has a different damage, passed through constructor
};

class Flame : public Projectile {
public:
    // Constructor/Destructor
    Flame(double x, double y, Direction dir, StudentWorld* world);
    ~Flame();
};

class Spray : public Projectile {
public:
    // Constructor/Destructor
    Spray(double x, double y, Direction dir, StudentWorld* world);
    ~Spray();
};

/////////////////////////////
// Goodies
/////////////////////////////
class Goodies : public Actor {
public:
    // Constructor/Destructor
    Goodies(int ID, double x, double y, StudentWorld* world, int lifetime);
    virtual ~Goodies() = 0;
    
    // Pure Virtual Function
    virtual void doEffect() = 0; // pure virtual function, class is abstract, needed to specialize goodie pickup effect
    
    // Virtual Function
    virtual void doSomething(); // checks if goodie is alive/touching socrates/has lifetime remaining
private:
    int m_lifetime; // all goodies have varying random lifetimes
};

class HealthKit : public Goodies {
public:
    // Constructor/Destructor
    HealthKit(double x, double y, StudentWorld* world, int lifespan);
    ~HealthKit();
    
    // Virtual Function
    virtual void doEffect();
};

class FlameCharge : public Goodies {
public:
    // Constructor/Destructor
    FlameCharge(double x, double y, StudentWorld* world, int lifespan);
    ~FlameCharge();
    
    // Virtual Function
    virtual void doEffect();
};

class ExtraLife : public Goodies {
public:
    // Constructor/Destructor
    ExtraLife(double x, double y, StudentWorld* world, int lifespan);
    ~ExtraLife();
    
    // Virtual Function
    virtual void doEffect();
};

class Fungus : public Goodies {
public:
    // Constructor/Destructor
    Fungus(double x, double y, StudentWorld* world, int lifespan);
    ~Fungus();
    
    // Virtual Function
    virtual void doEffect();
};

/////////////////////////////
// Pit
/////////////////////////////
class Pit : public Actor {
public:
    
    // Constructor/Destructor
    Pit(double x, double y, StudentWorld* world);
    ~Pit();
    
    // Virtual Functions
    virtual void doSomething();
    virtual bool blocksSpawns() const; // specialized virtual, needed for the world to know pits block spawning of pits/food/dirt
    virtual bool isDamageable() const; // specialized virtual, needed for the world to know pits cant be damaged
    virtual bool isEnemy() const; // specialized virtual, tells world pits are enemies
private:
    int m_numAggSalmonella; // inventory of bacteria
    int m_numSalmonella;
    int m_numEColi;
};

/////////////////////////////
// Bacteria
/////////////////////////////
class Bacteria : public Actor { //  no definition of doSomething, class is abstract
public:
    // Constructor/Destructor
    Bacteria(int ID, double x, double y, int health, StudentWorld* world);
    virtual ~Bacteria() = 0;
    
    // Virtual Functions
    virtual bool isEnemy() const; // specialized virtual, tells world bacteria are enemies
    virtual void takeDamage(int damage); // specialized virtual, decrements health
    virtual bool isEColi() const; // default virtual, overridden by ecoli
    
    // Mutator
    void ateFood(); // increments m_foodEaten, needed for derived classes to modify m_foodEaten thru eatFood
    
    // Other Functions
    bool duplicate(double& newX, double& newY); // does duplication if ready, passes new coords to class to create new object
    void adjustForMPD(); // does the mpd calculations for salmonella/agg. salmonella
private:
    int m_health; // each bacteria has a different health/loses health throughout gameplay
    int m_mpd; // each bacteria has a varying mpd (spec says ecoli starts at 0, even though mpd is never used)
    int m_foodEaten; // each bacteria can eat food from 0->3
};

class Salmonella : public Bacteria {
public:
    // Constructor/Destructor
    Salmonella(double x, double y, StudentWorld* world);
    ~Salmonella();
    
    // Virtual Function
    virtual void doSomething();
};

class AggSalmonella : public Bacteria { // incomplete - these get stuck on the border of the dish
public:
    // Constructor/Destructor
    AggSalmonella(double x, double y, StudentWorld* world);
    ~AggSalmonella();
    
    // Virtual Function
    virtual void doSomething();
};

class EColi : public Bacteria {
public:
    // Constructor/Destructor
    EColi(double x, double y, StudentWorld* world);
    ~EColi();
    
    // Virtual Functions
    virtual void doSomething();
    virtual bool isEColi() const; // specialized virtual, needed to play correct hurt/death sounds
};

#endif // ACTOR_H_
