#include <stdio.h>
#include <math.h>

// Function to calculate the distance between two points using latitude and longitude
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    double distance;
    
    // Convert latitude and longitude to radians
    double lat1Rad = lat1 * M_PI / 180;
    double lon1Rad = lon1 * M_PI / 180;
    double lat2Rad = lat2 * M_PI / 180;
    double lon2Rad = lon2 * M_PI / 180;
    
    // Calculate the differences between the latitudes and longitudes
    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;
    
    // Calculate the square of half the chord length between the points
    double a = pow(sin(deltaLat / 2), 2) + cos(lat1Rad) * cos(lat2Rad) * pow(sin(deltaLon / 2), 2);
    
    // Calculate the angular distance in radians
    double angularDistance = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    // Calculate the distance in kilometers using the Earth's radius
    double earthRadius = 6371;
    distance = angularDistance * earthRadius;
    
    return distance;
}

int main() {
    // Example usage
    double lat1 = 37.7749;
    double lon1 = -122.4194;
    double lat2 = 34.0522;
    double lon2 = -118.2437;
    
    double distance = calculateDistance(lat1, lon1, lat2, lon2);
    
    printf("Distance between the two points: %.2f km", distance);
    
    return 0;
}