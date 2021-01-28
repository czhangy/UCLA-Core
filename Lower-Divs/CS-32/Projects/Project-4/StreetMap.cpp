#include "provided.h"
#include "ExpandableHashMap.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

unsigned int hasher(const GeoCoord& g) {
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}

class StreetMapImpl {
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_map;
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_reverseMap;
};

StreetMapImpl::StreetMapImpl() {}

StreetMapImpl::~StreetMapImpl() {}

bool StreetMapImpl::load(string mapFile)
{
    ifstream inf(mapFile); // read file
    if (!inf)
        return false;  // file no open
    string line;
    while(getline(inf, line)) { // for the entire file, O(N)
        istringstream iss1(line);
        string streetName = line; // will always have correct format guaranteed by spec
        int numLines;
        string startLat; string startLon;
        string endLat; string endLon;
        getline(inf, line); // gets 2nd line of grouping
        istringstream iss2(line);
        iss2 >> numLines; // gets how many lines to read
        for (int i = 0; i < numLines; i++) { // reads the next numLines lines
            getline(inf, line);
            istringstream iss(line);
            iss >> startLat >> startLon >> endLat >> endLon; // fills variables w correct values
            GeoCoord start = GeoCoord(startLat, startLon);
            GeoCoord end = GeoCoord(endLat, endLon);
            StreetSegment s = StreetSegment(start, end, streetName);
            StreetSegment rev = StreetSegment(end, start, streetName);
            if (m_map.find(start) != nullptr) // geocoord already in map
                m_map.find(start)->push_back(s);
            else {
                vector<StreetSegment> temp;
                temp.push_back(s);
                m_map.associate(start, temp);
            }
            if (m_reverseMap.find(end) != nullptr) // geocoord already in map
                m_reverseMap.find(end)->push_back(rev);
            else {
                vector<StreetSegment> temp;
                temp.push_back(rev);
                m_reverseMap.associate(end, temp);
            }
        }
    }
    return true;
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const {
    for (auto iter = segs.begin(); iter != segs.end();) // make segs empty
        iter = segs.erase(iter);
    const vector<StreetSegment>* s1;
    const vector<StreetSegment>* s2;
    s1 = m_map.find(gc); // O(1)
    s2 = m_reverseMap.find(gc); // O(1)
    if (s1 == nullptr && s2 == nullptr) return false; // if not found in map
    if (s1 != nullptr)
        for (auto iter = s1->begin(); iter != s1->end(); iter++) // O(1)
            segs.push_back(*iter);
    if (s2 != nullptr)
        for (auto iter = s2->begin(); iter != s2->end(); iter++) // O(1)
            segs.push_back(*iter);
    return true;
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap() {
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap() {
    delete m_impl;
}

bool StreetMap::load(string mapFile) {
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const {
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
