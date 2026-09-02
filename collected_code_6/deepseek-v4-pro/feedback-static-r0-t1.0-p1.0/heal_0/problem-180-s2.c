#include <stdio.h>
#include <math.h>

#define EARTH_RADIUS_KM 6371.0
#define PI 3.14159265358979323846

double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double lat1_rad = degrees_to_radians(lat1);
    double lon1_rad = degrees_to_radians(lon1);
    double lat2_rad = degrees_to_radians(lat2);
    double lon2_rad = degrees_to_radians(lon2);
    
    double dlat = lat2_rad - lat1_rad;
    double dlon = lon2_rad - lon1_rad;
    
    double a = sin(dlat / 2.0) * sin(dlat / 2.0) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(dlon / 2.0) * sin(dlon / 2.0);
    
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return EARTH_RADIUS_KM * c;
}

int main(void) {
    double lat1 = 40.7128;
    double lon1 = -74.0060;
    double lat2 = 34.0522;
    double lon2 = -118.2437;
    
    double distance = calculate_distance(lat1, lon1, lat2, lon2);
    
    printf("Distance: %.2f km\n", distance);
    
    return 0;
}