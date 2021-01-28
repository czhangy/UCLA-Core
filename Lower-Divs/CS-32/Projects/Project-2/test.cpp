//
//  main.cpp
//  project2
//
//  Created by Charles Zhang on 1/22/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

// *** dump code ***
//void Map::dump() const {
//    if (size() == 0) std::cerr << "EMPTY MAP" << std::endl;
//    for (Node* ptr = m_head; ptr != nullptr; ptr = ptr->m_next) {
//        std::cerr << ptr->m_key << " | " << ptr->m_value << std::endl;
//    }
//}

#include <iostream>
#include <cassert>
#include "Map.h"
using namespace std;

void test();

int main() {
    test();
    cerr << endl << endl << endl;
    cerr << "****************" << endl << "ALL TESTS PASSED" << endl << "****************" << endl << endl;
}

void f() {
    Map one; // test deleting empty Map
    Map two; // test deleting Map with inserted elements
    two.insert("ifn", 23);
    two.insert("bf", 34783);
    two.insert("igfi", 923471);
    Map three(two); // test deleting copy constructed Map;
    Map four; // test deleting through erase
    four.insert("8374", 239846);
    four.erase("8374");
    Map five; // test deleting one element Map
    five.insert("sjdkb", 234);
}

void test() {
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;
    Map testMap;
    Map emptyMap;
    string str;
    double val;
    testMap.insert("key1", 1);

    ////////////////////////////////
    // Map() Tests
    ////////////////////////////////

    cerr << "Map() Tests:" << endl;
    assert(emptyMap.size() == 0); // should be 0
    cerr << "New Maps have size 0" << endl;
    assert(emptyMap.empty()); // a new map should be empty
    cerr << "New Maps are empty" << endl;
    cerr << endl << "Output:" << endl;
    emptyMap.dump(); // should print "EMPTY MAP"
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // empty() Tests
    ////////////////////////////////

    cerr << "empty() Tests:" << endl;
    assert(emptyMap.empty()); // a new map should be empty
    cerr << "Empty returns true on new Maps" << endl;
    assert(!testMap.empty()); // testMap is not empty
    cerr << "Empty returns false on Maps with elements" << endl;
    testMap.erase("key1");
    assert(testMap.empty()); // testMap is now empty
    cerr << "Empty returns true on erased Maps" << endl;
    cerr << endl << "Output:" << endl;
    emptyMap.dump(); // should print "EMPTY MAP"
    testMap.dump(); // should print "EMPTY MAP"
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // size() Tests
    ////////////////////////////////

    cerr << "size() Tests:" << endl;
    assert(testMap.size() == 0); // testMap should be empty
    cerr << "Size returns 0 on empty Maps" << endl;
    testMap.insert("key1", 1);
    testMap.insert("key2", 2);
    assert(testMap.size() == 2); // size() works after inserts
    cerr << "Size returns 2 on Maps with 2 elements" << endl;
    testMap.erase("key2");
    assert(testMap.size() == 1); // size() works after erase()
    cerr << "Size returns 1 after 1 element is erased" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // insert() Tests
    ////////////////////////////////

    cerr << "insert() Tests:" << endl;
    assert(testMap.insert("key2", 2)); // insert() returns correctly on success
    cerr << "Insert returns true on unknown keys" << endl;
    assert(!testMap.insert("key1", 1)); // insert() returns correctly on failure
    cerr << "Insert returns false on duplicate keys" << endl;
    assert(testMap.insert("key3", 2)); // insert() returns correctly on success
    cerr << "Insert returns true on duplicate values" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 2, key3 | 2
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // update() Tests
    ////////////////////////////////

    cerr << "update() Tests:" << endl;
    testMap.erase("key3");
    assert(!testMap.update("key3", 3)); // update() returns correctly on failure
    cerr << "Update returns false on deleted keys" << endl;
    assert(testMap.update("key2", 1)); // update() returns correctly on success
    cerr << "Update returns true on known keys" << endl;
    assert(!testMap.update("key4", 4)); // update() returns correctly on failure
    cerr << "Update returns false on unknown keys" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 1
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // insertOrUpdate() Tests
    ////////////////////////////////

    cerr << "insertOrUpdate() Tests:" << endl;
    assert(testMap.insertOrUpdate("key3", 3)); // insertOrUpdate() returns correctly on insert success
    cerr << "InsertOrUpdate returns true on insertion" << endl;
    assert(testMap.insertOrUpdate("key2", 2)); // insertOrUpdate() returns correctly on update success
    cerr << "InsertOrUpdate returns true on update" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 2, key3 | 3
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // erase() Tests
    ////////////////////////////////

    cerr << "erase() Tests:" << endl;
    assert(testMap.erase("key2")); // erase() returns correctly on success
    cerr << "Erase returns true on known keys" << endl;
    assert(testMap.erase("key3")); // erase() returns correctly on success
    cerr << "Erase returns correctly on the last Node" << endl;
    assert(testMap.erase("key1")); // erase() returns correctly on success
    cerr << "Erase returns correctly on the first Node" << endl;
    assert(!testMap.erase("key3")); // erase() returns correctly on failure
    cerr << "Erase returns false correctly on unknown keys" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print EMPTY MAP
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;
    
    testMap.insert("key1", 1);
    testMap.insert("key2", 2);

    ////////////////////////////////
    // contains() Tests
    ////////////////////////////////

    cerr << "contains() Tests:" << endl;
    assert(testMap.contains("key1")); // contains() returns correctly on success
    cerr << "Contains returns true on known keys" << endl;
    assert(!testMap.contains("notARealKey")); // contains() returns correctly on failure
    cerr << "Contains returns false on unknown keys" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 2
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // get() Version 1 Tests
    ////////////////////////////////

    cerr << "get() Version 1 Tests:" << endl;
    assert(testMap.get("key1", val)); // get() returns correctly on success
    cerr << "Get returns true on known keys" << endl;
    assert(val == 1); // get() maps correctly
    cerr << "Get maps values correctly" << endl;
    assert(!testMap.get("notARealKey", val)); // get() returns correctly on failure
    cerr << "Get returns false on unknown keys" << endl;
    assert(val == 1); // val is unchanged
    cerr << "Get failure doesn't reassign value" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 2
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // get() Version 2 Tests
    ////////////////////////////////
    val = 0;
    cerr << "get() Version 2 Tests:" << endl;
    assert(testMap.get(0, str, val)); // get() returns correctly on success
    cerr << "Get returns true on a valid index" << endl;
    assert(str == "key1" && val == 1); // get() maps correctly
    cerr << "Get maps keys and values correctly" << endl;
    assert(!testMap.get(-1, str, val)); // get() returns correctly on failure
    cerr << "Get returns false on negative indexes" << endl;
    assert(!testMap.get(testMap.size(), str, val)); // get() returns correctly on failure
    cerr << "Get returns false on out of bounds indexes" << endl;
    assert(str == "key1" && val == 1); // str and val are unchanged
    cerr << "Get failure doesn't reassign keys or values" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 | 1, key2 | 2
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // swap() Tests
    ////////////////////////////////

    str = "";
    val = 0;
    cerr << "swap() Tests:" << endl;
    testMap.swap(emptyMap);
    assert(testMap.empty()); // testMap is now empty
    cerr << "Swap makes testMap empty" << endl;
    assert(!emptyMap.empty()); // emptyMap now has elements
    cerr << "Swap makes emptyMap not empty" << endl;
    emptyMap.get(0, str, val);
    assert(str == "key1" && val == 1); // emptyMap has the correct first element
    cerr << "Swap transfers the first element correctly" << endl;
    emptyMap.get(1, str, val);
    assert(str == "key2" && val == 2); // emptyMap has the correct second element
    cerr << "Swap transfers the second element correctly" << endl;
    assert(emptyMap.size() == 2); // emptyMap has the correct size
    cerr << "Swap transfers the size correctly" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print EMPTY MAP
    emptyMap.dump(); // should print key1 | 1, key2 | 2
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    emptyMap.swap(testMap);

    ////////////////////////////////
    // combine() Tests
    ////////////////////////////////

    cerr << "combine() Tests:" << endl;
    Map m1; Map m2; Map m3;
    m1.insert("Fred", 123); m1.insert("Ethel", 456); m1.insert("Lucy", 789);
    m2.insert("Lucy", 789); m2.insert("Ricky", 321);
    assert(combine(m1, m2, m3)); // combine() returns correctly on success
    cerr << "Combine returns true correctly" << endl;
    assert(m3.contains("Fred") && m3.contains("Ricky") && m3.contains("Ethel") && m3.contains("Lucy")); //combine() maps to result correctly
    cerr << "Combine maps keys to result correctly" << endl;
    m2.update("Lucy", 654);
    assert(!combine(m1, m2, m3)); // combine returns correctly on failure
    cerr << "Combine returns false correctly" << endl;
    assert(m3.contains("Fred") && m3.contains("Ricky") && m3.contains("Ethel") && !m3.contains("Lucy")); // combine() re-maps correctly
    cerr << "Combine re-maps keys to result correctly" << endl;
    assert(!combine(m1, m2, m1)); // combine returns correctly when m1 and result are the same Map
    assert(m1.contains("Fred") && m1.contains("Ricky") && m1.contains("Ethel") && !m1.contains("Lucy")); // combine maps correctly when m1 and result are the same Map
    cerr << "Combine maps correctly when m1 and result refer to the same Map" << endl;
    cerr << endl << "Output:" << endl;
    m1.dump(); // should print Fred | 123, Ethel | 456, Ricky | 321 (order doesn't matter)
    m3.dump(); // should print Fred | 123, Ethel | 456, Ricky | 321 (order doesn't matter)
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // reassign() Tests
    ////////////////////////////////

    cerr << "reassign() Tests:" << endl;
    str = "";
    val = 0;
    testMap.insert("key3", 3);
    testMap.insert("key4", 4);
    testMap.insert("key5", 5);
    reassign(testMap, testMap);
    assert(testMap.contains("key1") && testMap.contains("key2") && testMap.contains("key3") && testMap.contains("key4") && testMap.contains("key5")); // the result contains all keys from the original
    cerr << "Reassign transfers all keys to the result" << endl;
    emptyMap.get("key1", val); // check if any key-value pairs match the original Map's
    assert(val != 1);
    testMap.get("key2", val);
    assert(val != 2);
    testMap.get("key3", val);
    assert(val != 3);
    testMap.get("key4", val);
    assert(val != 4);
    testMap.get("key5", val);
    assert(val != 5);
    cerr << "Reassign maps all keys to different values" << endl;
    cerr << "Reassign works when both maps refer to the same Map" << endl;
    cerr << endl << "Output:" << endl;
    testMap.dump(); // should print key1 - key5 with mismatching values
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // Copy Constructor Tests
    ////////////////////////////////
    cerr << "Copy Constructor Tests:" << endl;
    Map empty;
    Map newMap1(empty);
    assert(newMap1.size() == 0 && newMap1.empty()); // the copy constructor copies empty maps correctly
    cerr << "The copy constructor copies empty maps correctly" << endl;
    Map newMap2(testMap);
    assert(newMap2.contains("key1") && newMap2.contains("key2") && newMap2.contains("key3") && newMap2.contains("key4") && newMap2.contains("key5"));
    cerr << "The copy constructor copies normal maps correctly" << endl;
    cerr << endl << "Output:" << endl;
    newMap1.dump(); // should print EMPTY MAP
    newMap2.dump(); // should print key1 | 1, key2 | 2, key3 | 3, key4 | 4, key5 | 5
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;

    ////////////////////////////////
    // Destructor Tests
    ////////////////////////////////

    // Add "std::cerr << "Constructed" << std::endl;" every time a Node is created
    // Add "std::cerr << "Destructed" << std::endl;" every time a Node is deleted
    cerr << "Destructor Tests:" << endl;
    cerr << endl << "Output:" << endl;
    f(); // should print equal amounts of "Constructed" and "Destructed"
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl; // total prints 63 Destructed and Constructed

    ////////////////////////////////
    // Assignment Operator Tests
    ////////////////////////////////

    cerr << "Assignment Operator Tests:" << endl;
    Map imEmpty;
    m1 = imEmpty;
    assert(m1.size() == 0 &&  m1.empty());
    cerr << "The assignment operator works on empty Maps" << endl;
    imEmpty.insert("plsDontContainMe", 999);
    imEmpty = testMap;
    assert(imEmpty.contains("key1") && imEmpty.contains("key2") && imEmpty.contains("key3") && imEmpty.contains("key4") && imEmpty.contains("key5") && !imEmpty.contains("plsDontContainMe"));
    cerr << "The assignment operator copies all keys" << endl;
    cerr << endl << "Output:" << endl;
    imEmpty.dump(); // should print key1 | 1, key2 | 2, key3 | 3, key4 | 4, key5 | 5
    cerr << "--------------------" << endl;
    cerr << "--------------------" << endl;
}
