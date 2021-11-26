//
//  Map.cpp
//  project2
//
//  Created by Charles Zhang on 1/22/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include "Map.h"
#include <iostream>

Map::Map() : m_head(nullptr), m_tail(nullptr), m_size(0) {
}

Map::~Map() {
    for (Node* ptr = m_head; ptr != nullptr; ptr = m_head) { // start at the first object, assign ptr to head at the end of every loop
        m_head = m_head->m_next; // reassign head to the second object of the list
        delete ptr; // delete the old head
        std::cerr << "Destructed" << std::endl;
    }
}

Map::Map(const Map& other) : m_head(nullptr), m_tail(nullptr), m_size(other.m_size) {
    if (other.m_head == nullptr) return; // stop function if other is empty list
    Node* ptr = other.m_head; // can't be null
    Node* firstNode = new Node; // make first node
    std::cerr << "Constructed" << std::endl;
    m_head = firstNode;
    firstNode->m_key = ptr->m_key;
    firstNode->m_value = ptr->m_value;
    firstNode->m_next = nullptr;
    firstNode->m_last = nullptr;
    ptr = ptr->m_next; // might be null
    Node* last = firstNode; // will mark last Node
    for (Node* follow = firstNode; ptr != nullptr; ptr = ptr->m_next, follow = follow->m_next) {
        Node* lead = new Node;
        std::cerr << "Constructed" << std::endl;
        lead->m_last = follow;
        lead->m_value = ptr->m_value;
        lead->m_key = ptr->m_key;
        follow->m_next = lead;
        last = lead;
    }
    last->m_next = nullptr;
    m_tail = last;
}

Map& Map::operator=(const Map& other) {
    Map temp(other);
    swap(temp);
    return *this;
}

bool Map::empty() const {
    return m_head == nullptr;
}

int Map::size() const {
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    for (Node* ptr = m_head; ptr != nullptr; ptr = ptr->m_next) { // check the list for duplicate keys
        if (ptr->m_key == key) {
            return false;
        }
    }
    Node* newNode = new Node;
    std::cerr << "Constructed" << std::endl;
    newNode->m_key = key;
    newNode->m_value = value;
    if (m_tail == nullptr) { // if first insertion
        newNode->m_last = nullptr;
        newNode->m_next = nullptr;
        m_head = newNode;
        m_tail = newNode;
    } else {
        newNode->m_next = nullptr; // sets newNode at end of linked list
        newNode->m_last = m_tail;
        m_tail->m_next = newNode; // the Node pointed to by m_tail's m_next now points to the newNode
        m_tail = newNode; // the tail now points to the newNode
    }
    m_size++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    Node* ptr;
    for (ptr = m_head; ptr != nullptr && ptr->m_key != key; ptr = ptr->m_next) { // runs thru list, checking for m_key to be same as key, stops when that condition is satisfied or when it hits the end of the list
    }
    if (ptr == nullptr) { // if ptr is at end of list
        return false;
    }
    ptr->m_value = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return (update(key, value) || insert(key, value));
}

bool Map::erase(const KeyType& key) {
    Node* ptr;
    for (ptr = m_head; ptr != nullptr && ptr->m_key != key; ptr = ptr->m_next) { // align the ptr
    }
    if (ptr == nullptr) { // if at end of list, then return false, key doesn't exist
        return false;
    }
    if (ptr->m_last == nullptr) { // check if item is first in list
        m_head = ptr->m_next;
    } else {
        ptr->m_last->m_next = ptr->m_next;
    }
    if (ptr->m_next == nullptr) { // check if item is last in list
        m_tail = ptr->m_last;
    } else {
        ptr->m_next->m_last = ptr->m_last;
    }
    delete ptr;
    std::cerr << "Destructed" << std::endl;
    m_size--;
    return true;
}

bool Map::contains(const KeyType& key) const {
    Node* ptr;
    for (ptr = m_head; ptr != nullptr && ptr->m_key != key; ptr = ptr->m_next) {
    }
    return (ptr != nullptr); // if ptr is the nullptr, then the list doesn't contain key
}

bool Map::get(const KeyType& key, ValueType& value) const {
    Node* ptr;
    for (ptr = m_head; ptr != nullptr && ptr->m_key != key; ptr = ptr->m_next) { // loop through until key is found or end of list is hit
    }
    if (ptr == nullptr) { // if end of list is hit, return false
        return false;
    }
    value = ptr->m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    Node* ptr;
    int x = 0;
    for (ptr = m_head; ptr != nullptr && x < i; ptr = ptr->m_next, x++) { // loop through i times or until end of list is hit
        ;
    }
    if (ptr == nullptr || i < 0) { // if end of list is hit or i is negative, return false
        return false;
    }
    key = ptr->m_key;
    value = ptr->m_value;
    return true;
}

void Map::swap(Map& other) {
    Node* temp = m_head; // swaps heads
    m_head = other.m_head;
    other.m_head = temp;
    temp = m_tail; // swaps tails
    m_tail = other.m_tail;
    other.m_tail = temp;
    int val = m_size; // swaps sizes
    m_size = other.m_size;
    other.m_size = val;
}

void Map::dump() const {
    if (size() == 0) std::cerr << "EMPTY MAP" << std::endl;
    for (Node* ptr = m_head; ptr != nullptr; ptr = ptr->m_next) {
        std::cerr << ptr->m_key << " | " << ptr->m_value << std::endl;
    }
}

bool combine(const Map& m1, const Map& m2, Map& result) {
    bool noMismatch = true;
    Map temp;
    KeyType testKey;
    ValueType testVal;
    for (int i = 0; i < m1.size(); i++) { // loop thru all of the first map
        m1.get(i, testKey, testVal); // get the values for each node
        if (m2.contains(testKey)) { // check if in other map
            ValueType x;
            m2.get(testKey, x); // get corresponding value
            if (x == testVal) { // check if values are equal
                temp.insert(testKey, testVal);
            } else {
                noMismatch = false;
            }
        } else { // if not in other map, add to result
            temp.insert(testKey, testVal);
        }
    }
    for (int i = 0; i < m2.size(); i++) { // only needs to check unique keys in m2
        m2.get(i, testKey, testVal);
        if (!m1.contains(testKey)) {
            temp.insert(testKey, testVal);
        }
    }
    result = temp;
    return noMismatch; // return true if no mismatch
}

void reassign(const Map& m, Map& result) {
    Map temp;
    KeyType key;
    KeyType trashKey;
    ValueType value;
    ValueType trashValue;
    for (int i = 0; i < m.size() - 1; i++) { // loops through all keys except the last one
        m.get(i, key, trashValue);
        m.get(i + 1, trashKey, value); // gathers all values except the first one
        temp.insert(key, value); // inserts the ith key and the i+1th value
    }
    m.get(m.size() - 1, key, trashValue); // gets the last key
    m.get(0, trashKey, value); // gets the first value
    temp.insert(key, value); // maps the last key to the first value
    result = temp;
}
