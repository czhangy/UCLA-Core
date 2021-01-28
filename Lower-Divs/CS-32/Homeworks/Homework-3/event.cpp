//
//  main.cpp
//  hw3
//
//  Created by Charles Zhang on 2/7/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//////////////////////////
// Class Declarations
//////////////////////////

class Event {
public:
    Event(string name);
    virtual ~Event() {}
    string name() const;
    virtual bool isSport() const; // default to true
    virtual string need() const = 0;
private:
    string m_name;
};

class BasketballGame : public Event {
public:
    BasketballGame(string name);
    ~BasketballGame() {cout << "Destroying the " << name() << " basketball game" << endl;}
    string need() const;
private:
};

class Concert : public Event {
public:
    Concert(string name, string genre);
    ~Concert() {cout << "Destroying the " << name() << " " << m_genre << " concert" << endl;}
    bool isSport() const;
    string need() const;
private:
    string m_genre;
};

class HockeyGame : public Event {
public:
    HockeyGame(string name);
    ~HockeyGame() {cout << "Destroying the " << name() << " hockey game" << endl;}
    string need() const;
private:
};

//////////////////////////
// Event
//////////////////////////

Event::Event(string name) {
    m_name = name;
}

string Event::name() const {
    return m_name;
}

bool Event::isSport() const {
    return true;
}

//////////////////////////
// BasketballGame
//////////////////////////

BasketballGame::BasketballGame(string name) : Event(name) {}

string BasketballGame::need() const {
    return "hoops";
}

//////////////////////////
// Concert
//////////////////////////

Concert::Concert(string name, string genre) : Event(name), m_genre(genre) {}

bool Concert::isSport() const {
    return false;
}

string Concert::need() const {
    return "a stage";
}

//////////////////////////
// HockeyGame
//////////////////////////

HockeyGame::HockeyGame(string name) : Event(name) {}

string HockeyGame::need() const {
    return "ice";
}

void display(const Event* e)
{
    cout << e->name() << ": ";
    if (e->isSport())
    cout << "(sport) ";
    cout << "needs " << e->need() << endl;
}

int main()
{
    Event* events[5];
    events[0] = new BasketballGame("Lakers vs. Suns");
      // Concerts have a name and a genre.
    events[1] = new Concert("Banda MS", "banda");
    events[2] = new Concert("KISS", "hard rock");
    events[3] = new HockeyGame("Kings vs. Flames");

    cout << "Here are the events." << endl;
    for (int k = 0; k < 4; k++)
    display(events[k]);

      // Clean up the events before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
    delete events[k];
}
