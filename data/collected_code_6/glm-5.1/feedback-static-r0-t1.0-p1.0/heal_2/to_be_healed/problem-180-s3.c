#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double theta = lon1 - lon2;
    double dist = sin(lat1 * M_PI / 180.0) * sin(lat2 * M_PI / 180.0) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * cos(theta * M_PI / 180.0);
    if (dist > 1.0) {
        dist = 1.0;
    }
    if (dist < -1.0) {
        dist = -1.0;
    }
    dist = acos(dist);
    dist = dist * 180.0 / M_PI;
    dist = dist * 60.0 * 1.1515;
    return dist * 1.609344;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s lat1 lon1 lat2 lon2\n", argv[0]);
        return EXIT_FAILURE;
    }
    double lat1 = strtod(argv[1], NULL);
    double lon1 = strtod(argv[2], NULL);
    double lat2 = strtod(argv[3], NULL);
    double lon2 = strtod(argv[4], NULL);
    double distance = calculate_distance(lat1, lon1, lat2, lon2);
    printf("%f\n", distance);
    return EXIT_SUCCESS;
}