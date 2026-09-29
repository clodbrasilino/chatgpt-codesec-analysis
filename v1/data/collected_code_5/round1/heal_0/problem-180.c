#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define R 6371

typedef struct {
    double lat;
    double lon;
} Location;

double degrees_to_radians(double degrees) {
    return degrees * PI / 180;
}

double calculate_haversine_distance(Location loc1, Location loc2) {
    double lat1_rad = degrees_to_radians(loc1.lat);
    double lon1_rad = degrees_to_radians(loc1.lon);
    double lat2_rad = degrees_to_radians(loc2.lat);
    double lon2_rad = degrees_to_radians(loc2.lon);

    double lat_diff = lat2_rad - lat1_rad;
    double lon_diff = lon2_rad - lon1_rad;

    double a = sin(lat_diff / 2) * sin(lat_diff / 2) + cos(lat1_rad) * cos(lat2_rad) * sin(lon_diff / 2) * sin(lon_diff / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

int main() {
    Location loc1 = { .lat = 34.0522, .lon = -118.2437 };
    Location loc2 = { .lat = 37.7749, .lon = -122.4194 };

    double distance = calculate_haversine_distance(loc1, loc2);

    printf("The distance between the two locations is approximately %.2f km\n", distance);

    return 0;
}