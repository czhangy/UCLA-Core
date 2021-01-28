////
////  testnewMap.cpp
////  homework1
////
////  Created by Charles Zhang on 1/16/20.
////  Copyright © 2020 Charles Zhang. All rights reserved.
////
//
//#include <stdio.h>
//#include "newMap.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    Map m(2);
//    Map q(2);
//    string s1;
//    double x1;
//    q.insert("testKey", 123);
//
//    ////////////////////////////////
//    // empty Tests
//    ////////////////////////////////
//    assert(m.empty()); // empty success
//    assert(!q.empty()); // empty fails
//    cerr << endl;
//
//    ////////////////////////////////
//    // size Tests
//    ////////////////////////////////
//    assert(m.size() == 0); // new Maps have size 0
//    assert(q.size() == 1); // size success
//    q.insert("testKey2", 234);
//    assert(q.size() == 2); // size tracks inserts correctly
//    cerr << endl;
//
//    ////////////////////////////////
//    // insert Tests
//    ////////////////////////////////
//    assert(m.insert("k1", 1)); // insert success
//    assert(!m.insert("k1", 4)); // insert fails on duplicate keys
//    assert(!q.insert("testKey3", 567)); // insert fails when over limit
//    cerr << endl;
//
//    ////////////////////////////////
//    // update Tests
//    ////////////////////////////////
//    assert(m.update("k1", 2)); // update success
//    assert(!m.update("iAmNotAKey", 4)); // update failure on unknown keys
//    cerr << endl;
//
//    ////////////////////////////////
//    // insertOrUpdate Tests
//    ////////////////////////////////
//    assert(m.insertOrUpdate("k1", 3)); // updates instead of inserts
//    assert(m.insertOrUpdate("k2", 4)); // insert success
//    assert(m.insertOrUpdate("k2", 5)); // update works even at max limit
//    assert(!m.insertOrUpdate("k3", 8)); // insertOrUpdate fails when at max limit and with unknown key
//    cerr << endl;
//
//    ////////////////////////////////
//    // erase Tests
//    ////////////////////////////////
//    assert(m.erase("k1")); // erase success
//    assert(!m.erase("notARealKey")); // erase failure
//    cerr << endl;
//
//    ////////////////////////////////
//    // contains Tests
//    ////////////////////////////////
//    assert(m.contains("k2")); // contains success
//    assert(!m.contains("k1")); // contains failure
//    cerr << endl;
//
//    ////////////////////////////////
//    // get(1) Tests
//    ////////////////////////////////
//    assert(m.get("k2", x1)); // get success
//    assert(x1 == 5); // get maps correctly
//    q.get("testKey", x1);
//    assert(x1 == 123); // get maps correctly
//    assert(!m.get("notARealKey", x1)); // get failure on unknown key
//    assert(x1 == 123); // x1 not reassigned
//    cerr << endl;
//
//    ////////////////////////////////
//    // get(2) Tests
//    ////////////////////////////////
//    assert(m.get(0, s1, x1)); // get success
//    assert(s1 == "k2" && x1 == 5); // get maps correctly
//    assert(!m.get(m.size(), s1, x1)); // get fails on out of bounds
//    assert(!m.get(-1, s1, x1)); // get fails on negative indexes
//    assert(s1 == "k2" && x1 == 5); // s1 and x1 not reassigned
//    cerr << endl;
//
//
//    cerr << "All newMap tests passed" << endl;
//}
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert(10, "diez"));
    assert(m.insert(20, "veinte"));
    assert(m.size() == 2);
    ValueType v = "cuarenta y dos";
    assert(!m.get(30, v)  &&  v == "cuarenta y dos");
    assert(m.get(10, v)  &&  v == "diez");
    v = "cuarenta y dos";
    KeyType x = 30;
    assert(m.get(0, x, v)  &&
           ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
    KeyType x2 = 40;
    assert(m.get(1, x2, v)  &&
           ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
           x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
