//
//  CarMap.cpp
//  homework1
//
//  Created by Charles Zhang on 1/16/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include "CarMap.h"
#include "Map.h"
#include <iostream>

CarMap::CarMap() : m_map() {
};

bool CarMap::addCar(std::string license) {
    return m_map.insert(license, 0);
}

double CarMap::miles(std::string license) const {
    double value = -1;
    m_map.get(license, value);
    return value;
}

bool CarMap::drive(std::string license, double distance) {
    if (!m_map.contains(license) || distance < 0) return false;
    double value;
    m_map.get(license, value);
    return m_map.update(license, value + distance);
}

int CarMap::fleetSize() const {
    return m_map.size();
}

void CarMap::print() const {
    std::string s;
    double d;
    for (int i = 0; i < m_map.size(); i++) {
        m_map.get(i, s, d);
        std::cout << s << " " << d << std::endl;
    }
}
