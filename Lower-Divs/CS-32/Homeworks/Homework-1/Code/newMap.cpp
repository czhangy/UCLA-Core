//
//  newMap.cpp
//  homework1
//
//  Created by Charles Zhang on 1/16/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include <iostream>
#include "newMap.h"
using namespace std;

Map::Map(int capacity) : m_elements(0) {
    m_pairs = new Pairs[capacity];
    if (capacity < 0) {
        cout << "Capacity cannot be negative" << endl;
        exit(1);
    }
    m_max = capacity;
}

Map::~Map() {
    delete [] m_pairs;
}

Map::Map(const Map& other) {
    m_elements = other.m_elements;
    m_max = other.m_max;
    m_pairs = new Pairs[m_max];
    for (int i = 0; i < m_elements; i++) {
        m_pairs[i] = other.m_pairs[i];
    }
}

Map& Map::operator=(const Map& rhs) {
    delete [] m_pairs;
    m_elements = rhs.m_elements;
    m_max = rhs.m_max;
    m_pairs = new Pairs[m_max];
    for (int i = 0; i < m_elements; i++) {
        m_pairs[i] = rhs.m_pairs[i];
    }
    return *this;
}

bool Map::empty() const {
    return (m_elements == 0);
}

int Map::size() const {
    return m_elements;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (m_elements == m_max)
        return false;
    for (int i = 0; i < m_elements; i++) {
        if (key == m_pairs[i].m_key)
            return false;
    }
    m_pairs[m_elements].m_key = key;
    m_pairs[m_elements].m_value = value;
    m_elements++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    for (int i = 0; i < m_elements; i++) {
        if (key == m_pairs[i].m_key) {
            m_pairs[i].m_value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return (update(key, value) || insert(key, value));
}

bool Map::erase(const KeyType& key) {
    int i;
    for (i = 0; i < m_elements; i++) {
        if (key == m_pairs[i].m_key)
            break;
    }
    if (i == m_elements) return false;
    for (; i < m_elements - 1; i++) {
        m_pairs[i] = m_pairs[i+1];
    }
    m_elements--;
    return true;
}

bool Map::contains(const KeyType& key) const {
    for (int i = 0; i < m_elements; i++) {
        if (key == m_pairs[i].m_key)
            return true;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    for (int i = 0; i < m_elements; i++) {
        if (key == m_pairs[i].m_key) {
            value = m_pairs[i].m_value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (i < 0 || i >= m_elements)
        return false;
    key = m_pairs[i].m_key;
    value = m_pairs[i].m_value;
    return true;
}

void Map::swap(Map& other) {
    Map temp = other;
    other = *this;
    *this = temp;
}
