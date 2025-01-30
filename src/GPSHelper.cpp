#include <iostream>
#include <cmath>
#include <vector>
#include "GPSHelper.h"
#include"Order.h"
#include"Graph.h"


double GPSHelper::haversine(double lat1, double lon1, double lat2, double lon2) {
    // Radius of the Earth in kilometers
    const double R = 6371.0;
    
    // Convert latitude and longitude from degrees to radians
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    lon2 = lon2 * M_PI / 180.0;
    
    // Difference in coordinates
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    
    // Haversine formula
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) + std::cos(lat1) * std::cos(lat2) * std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    
    // Distance in kilometers
    double distance = R * c;
    return distance;
}

vector<vector<double>> GPSHelper:: getDistaceMatrix(vector<Location*> locations)
{
    std::vector<std::vector<double>> distances(locations.size(), std::vector<double>(locations.size(), 0.0));
    
    // Calculate distances between each pair of locations
    for (size_t i = 0; i < locations.size(); ++i) {
        for (size_t j = 0; j < locations.size(); ++j) {
            double lat1 = locations[i]->latitude;
            double lon1 = locations[i]->longitude;
            double lat2 = locations[j]->latitude;
            double lon2 = locations[j]->longitude;
            
            // Calculate the distance using Haversine formula
            distances[i][j] = haversine(lat1, lon1, lat2, lon2);
        }
    }
    return distances;

}

vector<vector<double>> GPSHelper:: getTimeMatrix(vector<vector<double>> distanceMatrix)
{
    std::vector<std::vector<double>> timeMatrix(distanceMatrix.size(), std::vector<double>(distanceMatrix.size(), 0.0));
    
    // Calculate distances between each pair of locations
    for (size_t i = 0; i < distanceMatrix.size(); ++i) {
        for (size_t j = 0; j < distanceMatrix.size(); ++j) {
            // Calculate the distance using Haversine formula
            timeMatrix[i][j] = distanceMatrix[i][j]/GPSHelper::SPEED;
        }
    }
    return timeMatrix;
}

