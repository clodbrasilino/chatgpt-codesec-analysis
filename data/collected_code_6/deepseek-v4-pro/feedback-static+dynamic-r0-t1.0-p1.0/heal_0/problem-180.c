#include <stdio.h>
#include <math.h>

#define EARTH_RADIUS_KM 6371.0
#define PI 3.14159265358979323846

double to_radians(double degrees) {
    return degrees * PI / 180.0;
}

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double lat1_rad = to_radians(lat1);
    double lon1_rad = to_radians(lon1);
    double lat2_rad = to_radians(lat2);
    double lon2_rad = to_radians(lon2);
    
    double dlat = lat2_rad - lat1_rad;
    double dlon = lon2_rad - lon1_rad;
    
    double a = sin(dlat / 2.0) * sin(dlat / 2.0) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(dlon / 2.0) * sin(dlon / 2.0);
    
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return EARTH_RADIUS_KM * c;
}

int main(void) {
    double lat1, lon1, lat2, lon2;
    
    printf("Enter latitude and longitude of first point (lat lon): ");
    if (scanf("%lf %lf", &lat1, &lon1) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter latitude and longitude of second point (lat lon): ");
    if (scanf("%lf %lf", &lat2, &lon2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (lat1 < -90.0 || lat1 > 90.0 || lat2 < -90.0 || lat2 > 90.0 ||
        lon1 < -180.0 || lon1 > 180.0 || lon2 < -180.0 || lon2 > 180.0) {
        fprintf(stderr, "Coordinates out of valid range\n");
        return 1;
    }
    
    double distance = calculate_distance(lat1, lon1, lat2, lon2);
    printf("Distance: %.2f km\n", distance);
    
    return 0;
}