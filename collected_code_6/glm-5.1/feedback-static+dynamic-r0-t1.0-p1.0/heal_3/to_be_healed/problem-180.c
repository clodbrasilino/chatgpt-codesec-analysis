#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double valid_lat_min = -90.0;
    double valid_lat_max = 90.0;
    double valid_lon_min = -180.0;
    double valid_lon_max = 180.0;

    if (lat1 < valid_lat_min || lat1 > valid_lat_max || lat2 < valid_lat_min || lat2 > valid_lat_max) {
        return -1.0;
    }

    if (lon1 < valid_lon_min || lon1 > valid_lon_max || lon2 < valid_lon_min || lon2 > valid_lon_max) {
        return -1.0;
    }

    double d_lat = (lat2 - lat1) * M_PI / 180.0;
    double d_lon = (lon2 - lon1) * M_PI / 180.0;

    double rad_lat1 = lat1 * M_PI / 180.0;
    double rad_lat2 = lat2 * M_PI / 180.0;

    double a = sin(d_lat / 2.0) * sin(d_lat / 2.0) +
               cos(rad_lat1) * cos(rad_lat2) *
               sin(d_lon / 2.0) * sin(d_lon / 2.0);

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double earth_radius_meters = 6371000.0;

    return earth_radius_meters * c;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <lat1> <lon1> <lat2> <lon2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1 = NULL;
    char *endptr2 = NULL;
    char *endptr3 = NULL;
    char *endptr4 = NULL;

    double lat1 = strtod(argv[1], &endptr1);
    double lon1 = strtod(argv[2], &endptr2);
    double lat2 = strtod(argv[3], &endptr3);
    double lon2 = strtod(argv[4], &endptr4);

    if (endptr1 == argv[1] || *endptr1 != '\0' ||
        endptr2 == argv[2] || *endptr2 != '\0' ||
        endptr3 == argv[3] || *endptr3 != '\0' ||
        endptr4 == argv[4] || *endptr4 != '\0') {
        fprintf(stderr, "Invalid coordinate format provided.\n");
        return EXIT_FAILURE;
    }

    double distance = calculate_distance(lat1, lon1, lat2, lon2);

    if (distance < 0.0) {
        fprintf(stderr, "Coordinates out of valid range.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", distance);

    return EXIT_SUCCESS;
}