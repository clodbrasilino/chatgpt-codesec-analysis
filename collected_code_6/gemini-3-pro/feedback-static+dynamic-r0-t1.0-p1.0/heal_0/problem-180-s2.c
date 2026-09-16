#include <stdio.h>
#include <math.h>

#define EARTH_RADIUS_KM 6371.0
#define PI 3.14159265358979323846

double to_radians(double degrees) {
    return degrees * PI / 180.0;
}

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    if (lat1 < -90.0 || lat1 > 90.0 || lat2 < -90.0 || lat2 > 90.0 ||
        lon1 < -180.0 || lon1 > 180.0 || lon2 < -180.0 || lon2 > 180.0) {
        return -1.0;
    }

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
    double lat1 = 52.2296756;
    double lon1 = 21.0122287;
    double lat2 = 41.8919300;
    double lon2 = 12.5113300;

    double distance = calculate_distance(lat1, lon1, lat2, lon2);

    if (distance < 0.0) {
        printf("Invalid coordinates provided.\n");
        return 1;
    }

    printf("%.2f\n", distance);

    return 0;
}