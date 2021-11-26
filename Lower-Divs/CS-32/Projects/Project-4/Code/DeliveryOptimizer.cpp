#include "provided.h"
#include <vector>
using namespace std;

class DeliveryOptimizerImpl {
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(const GeoCoord& depot, vector<DeliveryRequest>& deliveries, double& oldCrowDistance, double& newCrowDistance) const;
private:
    double getCrowsDistance(const vector<DeliveryRequest>& v, const GeoCoord& depot) const;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm) {}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl() {}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(const GeoCoord& depot, vector<DeliveryRequest>& deliveries, double& oldCrowDistance, double& newCrowDistance) const {
    GeoCoord currentLoc = depot;
    vector<DeliveryRequest> temp;
    oldCrowDistance = getCrowsDistance(deliveries, depot);
    
    while (!deliveries.empty()) {
        double minDist = 1234567890; // arbitrary initial
        auto closestLoc = deliveries.begin();
        for (auto iter = deliveries.begin(); iter != deliveries.end(); iter++) { // find closest dist.
            if (distanceEarthMiles(currentLoc, iter->location) < minDist) {
                minDist = distanceEarthMiles(currentLoc, (*iter).location);
                closestLoc = iter;
            }
        }
        temp.push_back(*closestLoc); // push closest location into new array
        currentLoc = (*closestLoc).location; // set new current location
        deliveries.erase(closestLoc); // delete the current location from the remaining vector
    }
    deliveries = temp; // set deliveries to new vector
    
    newCrowDistance = getCrowsDistance(deliveries, depot);
}

double DeliveryOptimizerImpl::getCrowsDistance(const vector<DeliveryRequest>& v, const GeoCoord& depot) const {
    double dist = 0;
    for (int i = 0; i + 1 < v.size(); i++)
        dist += distanceEarthMiles(v[i].location, v[i + 1].location);
    dist += distanceEarthMiles(depot, v.front().location);
    dist += distanceEarthMiles(v.back().location, depot);
    return dist;
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm) {
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer() {
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(const GeoCoord& depot, vector<DeliveryRequest>& deliveries, double& oldCrowDistance, double& newCrowDistance) const {
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
