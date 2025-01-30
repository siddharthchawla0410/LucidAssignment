#pragma once
#include "Location.h"
#include "Graph.h"
#include<vector>
using namespace std;

class GPSHelper 
{
    public:
    // static const double SPEED=20;
    static constexpr double SPEED = 20.0;  // Use constexpr for non-integral types
    GPSHelper();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    static vector<vector<double>> getDistaceMatrix(vector<Location*> locations);
    static vector<vector<double>> getTimeMatrix(vector<vector<double>> distanceMatrix);
    // static vector<Node<double>*> createNodes(vector<Order*> orders);
};