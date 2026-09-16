#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const double EARTH_RADIUS_KM = 6371.0088;

static double degrees_to_radians(double degrees)
{
    return degrees * (acos(-1.0) / 180.0);
}

static int calculate_distance(double latitude1, double longitude1,
                              double latitude2, double longitude2,
                              double *distance_km)
{
    double lat1;
    double lat2;
    double delta_lat;
    double delta_lon;
    double sin_half_lat;
    double sin_half_lon;
    double a;

    if (distance_km == NULL ||
        !isfinite(latitude1) || !isfinite(longitude1) ||
        !isfinite(latitude2) || !isfinite(longitude2) ||
        latitude1 < -90.0 || latitude1 > 90.0 ||
        latitude2 < -90.0 || latitude2 > 90.0 ||
        longitude1 < -180.0 || longitude1 > 180.0 ||
        longitude2 < -180.0 || longitude2 > 180.0) {
        return -1;
    }

    lat1 = degrees_to_radians(latitude1);
    lat2 = degrees_to_radians(latitude2);
    delta_lat = degrees_to_radians(latitude2 - latitude1);
    delta_lon = degrees_to_radians(longitude2 - longitude1);
    sin_half_lat = sin(delta_lat / 2.0);
    sin_half_lon = sin(delta_lon / 2.0);

    a = sin_half_lat * sin_half_lat +
        cos(lat1) * cos(lat2) * sin_half_lon * sin_half_lon;

    if (a < 0.0) {
        a = 0.0;
    } else if (a > 1.0) {
        a = 1.0;
    }

    *distance_km =
        2.0 * EARTH_RADIUS_KM * atan2(sqrt(a), sqrt(1.0 - a));

    return isfinite(*distance_km) ? 0 : -1;
}

static int parse_coordinate(const char *text, double *value)
{
    char *end;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || end == NULL ||
        *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    double latitude1;
    double longitude1;
    double latitude2;
    double longitude2;
    double distance_km;

    if (argc != 5) {
        fprintf(stderr, "Usage: %s <lat1> <lon1> <lat2> <lon2>\n",
                argv[0] != NULL ? argv[0] : "distance");
        return EXIT_FAILURE;
    }

    if (parse_coordinate(argv[1], &latitude1) != 0 ||
        parse_coordinate(argv[2], &longitude1) != 0 ||
        parse_coordinate(argv[3], &latitude2) != 0 ||
        parse_coordinate(argv[4], &longitude2) != 0) {
        fprintf(stderr, "Invalid numeric coordinate.\n");
        return EXIT_FAILURE;
    }

    if (calculate_distance(latitude1, longitude1,
                           latitude2, longitude2,
                           &distance_km) != 0) {
        fprintf(stderr, "Coordinates are outside their valid ranges.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.3f km\n", distance_km) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}