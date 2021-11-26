//
//  testCarMap.cpp
//  homework1
//
//  Created by Charles Zhang on 1/16/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cassert>
#include "CarMap.h"
using namespace std;

int main() {
    CarMap c;
    CarMap x;
    
    ////////////////////////////////
    // addCar Tests
    ////////////////////////////////
    assert(c.addCar("l1")); // addCar succeeds
    assert(!c.addCar("l1")); // addCar fails on duplicate license plates
    c.addCar("l2");
    c.print(); // should print l1 0, l2 0
    cerr << endl;

    ////////////////////////////////
    // miles Tests
    ////////////////////////////////
    assert(c.miles("l1") == 0 && c.miles("l2") == 0); // miles succeeds
    assert(c.miles("l3") == -1); // miles fails on unknown license plates
    c.print(); // should print l1 0, l2 0
    cerr << endl;
    
    ////////////////////////////////
    // drive Tests
    ////////////////////////////////
    assert(c.drive("l1", 2) && c.drive("l2", 8) && c.drive("l1", 3)); // drive succeeds
    assert(!c.drive("l3", 2)); // drive fails on unknown licenses
    assert(!c.drive("l1", -4)); // drive fails on negative distances
    assert(c.miles("l1") == 5 && c.miles("l2") == 8); // miles updates correctly
    c.print(); // should print l1 5 l2 8
    cerr << endl;
    
    ////////////////////////////////
    // fleetSize Tests
    ////////////////////////////////
    assert(x.fleetSize() == 0); // fleetSize is 0 on empty CarMaps
    x.addCar("newCar");
    assert(x.fleetSize() == 1); // fleetSize updates correctly
    c.print(); // should print l1 5 l2 8
    cerr << endl;

    cerr << "All CarMap tests passed" << endl;
}

