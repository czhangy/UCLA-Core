////
////  testMap.cpp
////  homework1
////
////  Created by Charles Zhang on 1/16/20.
////  Copyright © 2020 Charles Zhang. All rights reserved.
////
//
#include <stdio.h>
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;
    Map q;
    string s1;
    double x1;
    q.insert("testKey", 123);

    ////////////////////////////////
    // empty Tests
    ////////////////////////////////
    assert(m.empty()); // empty success
    assert(!q.empty()); // empty fails
    cerr << endl;

    ////////////////////////////////
    // size Tests
    ////////////////////////////////
    assert(m.size() == 0); // new Maps have size 0
    assert(q.size() == 1); // size success
    q.insert("testKey2", 234);
    assert(q.size() == 2); // size tracks inserts correctly
    cerr << endl;

    ////////////////////////////////
    // insert Tests
    ////////////////////////////////
    assert(m.insert("k1", 1)); // insert success
    assert(!m.insert("k1", 4)); // insert fails on duplicate keys
    cerr << endl;

    ////////////////////////////////
    // update Tests
    ////////////////////////////////
    assert(m.update("k1", 2)); // update success
    assert(!m.update("iAmNotAKey", 4)); // update failure on unknown keys
    cerr << endl;

    ////////////////////////////////
    // insertOrUpdate Tests
    ////////////////////////////////
    assert(m.insertOrUpdate("k1", 3)); // updates instead of inserts
    assert(m.insertOrUpdate("k2", 4)); // insert success
    assert(m.insertOrUpdate("k2", 5)); // update works even at max limit
    cerr << endl;

    ////////////////////////////////
    // erase Tests
    ////////////////////////////////
    assert(m.erase("k1")); // erase success
    assert(!m.erase("notARealKey")); // erase failure
    cerr << endl;

    ////////////////////////////////
    // contains Tests
    ////////////////////////////////
    assert(m.contains("k2")); // contains success
    assert(!m.contains("k1")); // contains failure
    cerr << endl;

    ////////////////////////////////
    // get(1) Tests
    ////////////////////////////////
    assert(m.get("k2", x1)); // get success
    assert(x1 == 5); // get maps correctly
    q.get("testKey", x1);
    assert(x1 == 123); // get maps correctly
    assert(!m.get("notARealKey", x1)); // get failure on unknown key
    assert(x1 == 123); // x1 not reassigned
    cerr << endl;

    ////////////////////////////////
    // get(2) Tests
    ////////////////////////////////
    assert(m.get(0, s1, x1)); // get success
    assert(s1 == "k2" && x1 == 5); // get maps correctly
    assert(!m.get(m.size(), s1, x1)); // get fails on out of bounds
    assert(!m.get(-1, s1, x1)); // get fails on negative indexes
    assert(s1 == "k2" && x1 == 5); // s1 and x1 not reassigned
    cerr << endl;


    cerr << "All Map tests passed" << endl;
}

