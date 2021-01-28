#include "provided.h"
#include <vector>
using namespace std;

const string NO_TURN = "";

class DeliveryPlannerImpl {
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries, vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const;
private:
    DeliveryOptimizer m_optimizer;
    PointToPointRouter m_router;
    string translateAngle(double angle) const;
};

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm) : m_optimizer(sm), m_router(sm) {}

DeliveryPlannerImpl::~DeliveryPlannerImpl() {}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries, vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const {
    
    // variable initialization
    double temp;
    totalDistanceTravelled = 0;
    for (auto iter = commands.begin(); iter != commands.end();)
        iter = commands.erase(iter);
    vector<DeliveryRequest> optimizedOrder;
    vector<StreetSegment> totalSegments;
    for (int i = 0; i < deliveries.size(); i++) // make new vector to get new order
        optimizedOrder.push_back(deliveries[i]);
    m_optimizer.optimizeDeliveryOrder(depot, optimizedOrder, temp, temp); // get optimized order
    optimizedOrder.push_back(DeliveryRequest("", depot)); // put depot in as last instruction for return
    GeoCoord start = depot;
    
    // getting route in terms of segments
    for (int i = 0; i < optimizedOrder.size(); i++) { // for each of the destinations
        list<StreetSegment> partialRoute; // list to take each of the segments
        double partialDist; // double to take the partial distance
        if (m_router.generatePointToPointRoute(start, optimizedOrder[i].location, partialRoute, partialDist) != DELIVERY_SUCCESS) // get segments from one loc to the next
            return m_router.generatePointToPointRoute(start, optimizedOrder[i].location, partialRoute, partialDist); // return failure status
        start = optimizedOrder[i].location; // update deliverer's location
        for (auto iter = partialRoute.begin(); iter != partialRoute.end(); iter++) { // update overall segments
            totalSegments.push_back(*iter);
        }
    } // loop exits with vector of segments leading to all locations
    
    // translates segments into instructions
    int deliveryTracker = 0; // tracks which # delivery is occurring
    bool needToDeliver = false; // tracks if at destinationx
    string prevStreet = NO_TURN;
    for (int i = 0; i + 1 < totalSegments.size();) {
        DeliveryCommand cmd;
        double dist = 0; // keep track of how long to follow a street for
        string dir = translateAngle(angleOfLine(totalSegments[i])); // gets angle of line, puts it into dir
        dist += distanceEarthMiles(totalSegments[i].start, totalSegments[i].end); // add segment distance
        
        if (totalSegments[i].end == depot) break; // returned to depot
        
        if (needToDeliver) { // if at delivery location
            needToDeliver = false;
            cmd.initAsDeliverCommand(optimizedOrder[deliveryTracker].item);
            deliveryTracker++;
            prevStreet = NO_TURN;
            commands.push_back(cmd); // puts cmd into final vector
            continue;
        }
        
        if (prevStreet != NO_TURN && angleBetween2Lines(totalSegments[i - 1], totalSegments[i]) >= 1 && angleBetween2Lines(totalSegments[i - 1], totalSegments[i]) <= 359) { // if a turn should happen
            if (angleBetween2Lines(totalSegments[i - 1], totalSegments[i]) >= 180)
                cmd.initAsTurnCommand("right", totalSegments[i].name);
            else
                cmd.initAsTurnCommand("left", totalSegments[i].name);
            prevStreet = NO_TURN;
            commands.push_back(cmd); // puts cmd into final vector
            continue;
        }
        
        while (totalSegments[i + 1].name == totalSegments[i].name) { // while next segment on same street
            i++; // move to next segment
            dist += distanceEarthMiles(totalSegments[i].start, totalSegments[i].end); // add new segment distance
            if (totalSegments[i].start == optimizedOrder[deliveryTracker].location) { // if destination reached
                cmd.initAsProceedCommand(dir, totalSegments[i].name, dist);
                totalDistanceTravelled += dist;
                needToDeliver = true;
                break;
            }
        }
        
        if (!needToDeliver) { // normal proceed
            if (totalSegments[i].end == optimizedOrder[deliveryTracker].location) { // if destination reached
                cmd.initAsProceedCommand(dir, totalSegments[i].name, dist);
                totalDistanceTravelled += dist;
                needToDeliver = true;
            } else {
                cmd.initAsProceedCommand(dir, totalSegments[i].name, dist);
                prevStreet = totalSegments[i].name;
                totalDistanceTravelled += dist;
                i++;
            }
        }
        
        commands.push_back(cmd); // puts cmd into final vector
    }
    return DELIVERY_SUCCESS;
}

string DeliveryPlannerImpl::translateAngle(double angle) const { // 0 <= angle <= 360
    if (angle >= 337.5)
        return "east";
    else if (angle >= 292.5)
        return "southeast";
    else if (angle >= 247.5)
        return "south";
    else if (angle >= 202.5)
        return "southwest";
    else if (angle >= 157.5)
        return "west";
    else if (angle >= 112.5)
        return "northwest";
    else if (angle >= 67.5)
        return "north";
    else if (angle >= 22.5)
        return "northeast";
    else return "east";
}

//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm) {
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner() {
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(const GeoCoord& depot, const vector<DeliveryRequest>& deliveries, vector<DeliveryCommand>& commands, double& totalDistanceTravelled) const {
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
