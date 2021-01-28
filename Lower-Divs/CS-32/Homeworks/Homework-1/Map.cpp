////
////  Map.cpp
////  homework1
////
////  Created by Charles Zhang on 1/15/20.
////  Copyright © 2020 Charles Zhang. All rights reserved.
////
//
#include <iostream>
#include "Map.h"

Map::Map() : m_elements(0) {
}

bool Map::empty() const {
    return (m_elements == 0);
}

int Map::size() const {
    return m_elements;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    if (m_elements == DEFAULT_MAX_ITEMS)
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
    KeyType tempKey;
    ValueType tempValue;
    for (int i = 0; i < this->size() || i < other.size(); i++) {
        tempKey = m_pairs[i].m_key;
        m_pairs[i].m_key = other.m_pairs[i].m_key;
        other.m_pairs[i].m_key = tempKey;
        tempValue = m_pairs[i].m_value;
        m_pairs[i].m_value = other.m_pairs[i].m_value;
        other.m_pairs[i].m_value = tempValue;
    }
    int temp = m_elements;
    m_elements = other.m_elements;
    other.m_elements = temp;
}

void Map::dump() const {
    if (empty()) {
        std::cerr << "EMPTY" << std::endl;
    }
    for (int i = 0; i < m_elements; i++)
        std::cerr << i << ": " << m_pairs[i].m_key << " | " << m_pairs[i].m_value << std::endl;
}
