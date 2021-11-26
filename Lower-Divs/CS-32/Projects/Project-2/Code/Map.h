//
//  Map.hpp
//  project2
//
//  Created by Charles Zhang on 1/22/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <stdio.h>
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;
private:
    struct Node {
        KeyType m_key;
        ValueType m_value;
        Node* m_next;
        Node* m_last;
    };
    Node* m_head;
    Node* m_tail;
    int m_size;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif /* Map_h */
