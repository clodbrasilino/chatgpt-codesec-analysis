#include <stdio.h>
#include <math.h>

#define EARTH_RADIUS_KM 6371.0
#define PI 3.14159265358979323846

typedef struct {
    double latitude;
    double longitude;
} Coordinate;

static double to_radians(double degrees) {
    return degrees * PI / 180.0;
}

static int validate_coordinate(const Coordinate *coord) {
    if (coord == NULL) {
        return 0;
    }
    if (coord->latitude < -90.0 || coord->latitude > 90.0) {
        return 0;
    }
    if (coord->longitude < -180.0 || coord->longitude > 180.0) {
        return 0;
    }
    return 1;
}

double calculate_distance(const Coordinate *point1, const Coordinate *point2, int *error) {
    double lat1_rad;
    double lat2_rad;
    double delta_lat;
    double delta_lon;
    double a;
    double c;
    
    if (error == NULL) {
        return -1.0;
    }
    
    *error = 0;
    
    if (!validate_coordinate(point1) || !validate_coordinate(point2)) {
        *error = 1;
        return -1.0;
    }
    
    lat1_rad = to_radians(point1->latitude);
    lat2_rad = to_radians(point2->latitude);
    delta_lat = to_radians(point2->latitude - point1->latitude);
    delta_lon = to_radians(point2->longitude - point1->longitude);
    
    a = sin(delta_lat / 2.0) * sin(delta_lat / 2.0) +
        cos(lat1_rad) * cos(lat2_rad) *
        sin(delta_lon / 2.0) * sin(delta_lon / 2.0);
    
    c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return EARTH_RADIUS_KM * c;
}

int main(void) {
    Coordinate point1 = {40.7128, -74.0060};
    Coordinate point2 = {51.5074, -0.1278};
    double distance;
    int error;
    
    distance = calculate_distance(&point1, &point2, &error);
    
    if (error != 0) {
        fprintf(stderr, "Error: Invalid coordinates provided\n");
        return 1;
    }
    
    printf("Distance between points: %.2f km\n", distance);
    
    return 0;
}