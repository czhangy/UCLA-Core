#include "provided.h"
#include "ExpandableHashMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

bool loadDeliveryRequests(string deliveriesFile, GeoCoord& depot, vector<DeliveryRequest>& v);
bool parseDelivery(string line, string& lat, string& lon, string& item);

int main(int argc, char *argv[]) {
//    if (argc != 3) {
//        cout << "Usage: " << argv[0] << " mapdata.txt deliveries.txt" << endl;
//        return 1;
//    }

    StreetMap sm;
// /Users/charleszhang/Desktop/mapdata.txt
// /w/home.26/cs/ugrad/charlesx/proj4/mapdata.txt
    if (!sm.load("/w/home.26/cs/ugrad/charlesx/proj4/mapdata.txt")) {
        cout << "Unable to load map data file " << argv[1] << endl;
        return 1;
    }
// /w/home.26/cs/ugrad/charlesx/proj4/deliveries.txt
// /Users/charleszhang/Desktop/deliveries.txt
    GeoCoord depot;
    vector<DeliveryRequest> deliveries;
    if (!loadDeliveryRequests("/w/home.26/cs/ugrad/charlesx/proj4/deliveries.txt", depot, deliveries)) {
        cout << "Unable to load delivery request file " << argv[2] << endl;
        return 1;
    }

    cout << "Generating route...\n";

    DeliveryPlanner dp(&sm);
    vector<DeliveryCommand> dcs;
    double totalMiles;
    DeliveryResult result = dp.generateDeliveryPlan(depot, deliveries, dcs, totalMiles);
    if (result == BAD_COORD) {
        cout << "One or more depot or delivery coordinates are invalid." << endl;
        return 1;
    }
    if (result == NO_ROUTE) {
        cout << "No route can be found to deliver all items." << endl;
        return 1;
    }
    cout << "Starting at the depot...\n";
    for (const auto& dc : dcs)
        cout << dc.description() << endl;
    cout << "You are back at the depot and your deliveries are done!\n";
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << totalMiles << " miles travelled for all deliveries." << endl;
}

bool loadDeliveryRequests(string deliveriesFile, GeoCoord& depot, vector<DeliveryRequest>& v) {
    ifstream inf(deliveriesFile);
    if (!inf)
        return false;
    string lat;
    string lon;
    inf >> lat >> lon;
    inf.ignore(10000, '\n');
    depot = GeoCoord(lat, lon);
    string line;
    while (getline(inf, line))
    {
        string item;
        if (parseDelivery(line, lat, lon, item))
            v.push_back(DeliveryRequest(item, GeoCoord(lat, lon)));
    }
    return true;
}

bool parseDelivery(string line, string& lat, string& lon, string& item) {
    const size_t colon = line.find(':');
    if (colon == string::npos) {
        cout << "Missing colon in deliveries file line: " << line << endl;
        return false;
    }
    istringstream iss(line.substr(0, colon));
    if (!(iss >> lat >> lon)) {
        cout << "Bad format in deliveries file line: " << line << endl;
        return false;
    }
    item = line.substr(colon + 1);
    if (item.empty()) {
        cout << "Missing item in deliveries file line: " << line << endl;
        return false;
    }
    return true;
}

