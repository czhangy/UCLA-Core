#include "provided.h"
#include "ExpandableHashMap.h"
#include <list>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

class PointToPointRouterImpl {
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end, list<StreetSegment>& route, double& totalDistanceTravelled) const;
private:
    const StreetMap* m_map;
    double streetLength(const GeoCoord& g1, const GeoCoord& g2) const;
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm) : m_map(sm) {}

PointToPointRouterImpl::~PointToPointRouterImpl() {}

// Logic :
// Push coordinates onto the queue
// Analyze the front of the queue, push new endpoints back on the queue
// Check if the front of the queue is yay
    // if it is then add that to the possible successes?
        // maybe not this sounds like a bad idea :(
        // trace back using map to get complete route
    // if not then fuck keep going
// Map the added coords to the currently analyzed coord so we can trace back later

// Problems :
// My IQ is < 50
// Everything
// fuck big O, is this O(N)?


DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end, list<StreetSegment>& route, double& totalDistanceTravelled) const {
    for (auto iter = route.begin(); iter != route.end();) // clear current list
        iter = route.erase(iter);
    totalDistanceTravelled = 0; // reset dist.
    queue<GeoCoord> testCoord; // holds next coords to test
    ExpandableHashMap<GeoCoord, GeoCoord> prevLoc; // maps coord to parent coord

    if (start == end) // boundary case
        return DELIVERY_SUCCESS;
    
    testCoord.push(start);
    while (!testCoord.empty()) { // loop until segments are run out
        GeoCoord test = testCoord.front(); // get next test point
        testCoord.pop();
        if (test == end) { // destination found
            while (*prevLoc.find(test) != start) { // loops until beginning
                vector<StreetSegment> temp;
                m_map->getSegmentsThatStartWith(*prevLoc.find(test), temp);
                for (auto iter = temp.begin(); iter != temp.end(); iter++) { // find the right segment out of the mapped segments
                    if ((*iter).end == test) {
                        route.push_front(*iter); // push segment to front
                        totalDistanceTravelled += streetLength((*iter).start, (*iter).end);
                        break;
                    }
                }
                test = *prevLoc.find(test); // continue backwards
            }
            vector<StreetSegment> temp; // get very first segment
            m_map->getSegmentsThatStartWith(*prevLoc.find(test), temp);
            for (auto iter = temp.begin(); iter != temp.end(); iter++) {
                if ((*iter).end == test) {
                    route.push_front(*iter); // push segment to front
                    totalDistanceTravelled += streetLength((*iter).start, (*iter).end);
                    break;
                }
            }
            return DELIVERY_SUCCESS;
        }
        vector<StreetSegment> endpoints;
        if (!m_map->getSegmentsThatStartWith(test, endpoints)) // get all points it connects to
            return BAD_COORD; // not in map
        for (auto iter = endpoints.begin(); iter != endpoints.end(); iter++) { // pushes all endpoints into testCoord if they are shortest path so far (not efficient but oh well i tried)
            if (prevLoc.find((*iter).end) == nullptr) {// new GeoCoord
                prevLoc.associate((*iter).end, (*iter).start); // link end to start
                testCoord.push((*iter).end);
            } else { // GeoCoord already made, check past route compare to new route
                GeoCoord tracer = (*iter).start;
                double newTotal = 0, oldTotal = 0;
                while (tracer != start) {
                    newTotal += streetLength(tracer, *prevLoc.find(tracer)); // get distance between start and end of current tested streets
                    tracer = *prevLoc.find(tracer); // iterate backwards
                }
                tracer = *prevLoc.find((*iter).end);
                while (tracer != start) {
                    oldTotal += streetLength(tracer, *prevLoc.find(tracer)); // get distance between start and end of old streets
                    tracer = *prevLoc.find(tracer); // iterate backwards
                }
                if (newTotal < oldTotal) { // if the new route is better
                    testCoord.push((*iter).end);
                    prevLoc.associate((*iter).end, (*iter).start);
                }
            }
        }
    }
    return NO_ROUTE;  // Delete this line and implement this function correctly
}

double PointToPointRouterImpl::streetLength(const GeoCoord& g1, const GeoCoord& g2) const {
    return sqrt(pow(g1.latitude - g2.latitude, 2) + pow(g1.longitude - g2.longitude, 2)); // return length of a street segment
}
//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code

PointToPointRouter::PointToPointRouter(const StreetMap* sm) {
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter() {
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(const GeoCoord& start, const GeoCoord& end, list<StreetSegment>& route, double& totalDistanceTravelled) const {
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
