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
    double latitude_delta;
    double longitude_delta;
    double sin_half_latitude_delta;
    double sin_half_longitude_delta;
    double a;
    double c;

    if (distance_km == NULL ||
        !isfinite(latitude1) || !isfinite(longitude1) ||
        !isfinite(latitude2) || !isfinite(longitude2) ||
        latitude1 < -90.0 || latitude1 > 90.0 ||
        latitude2 < -90.0 || latitude2 > 90.0 ||
        longitude1 < -180.0 || longitude1 > 180.0 ||
        longitude2 < -180.0 || longitude2 > 180.0) {
        return -1;
    }

    latitude_delta = degrees_to_radians(latitude2 - latitude1);
    longitude_delta = degrees_to_radians(longitude2 - longitude1);
    latitude1 = degrees_to_radians(latitude1);
    latitude2 = degrees_to_radians(latitude2);

    sin_half_latitude_delta = sin(latitude_delta / 2.0);
    sin_half_longitude_delta = sin(longitude_delta / 2.0);

    a = sin_half_latitude_delta * sin_half_latitude_delta +
        cos(latitude1) * cos(latitude2) *
        sin_half_longitude_delta * sin_half_longitude_delta;

    if (a < 0.0) {
        a = 0.0;
    } else if (a > 1.0) {
        a = 1.0;
    }

    c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    *distance_km = EARTH_RADIUS_KM * c;

    return isfinite(*distance_km) ? 0 : -1;
}

static int parse_coordinate(const char *text, double *value)
{
    char *end;
    double parsed_value;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed_value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed_value)) {
        return -1;
    }

    *value = parsed_value;
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
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "distance";

        fprintf(stderr,
                "Usage: %s <latitude1> <longitude1> <latitude2> <longitude2>\n",
                program_name);
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
                           latitude2, longitude2, &distance_km) != 0) {
        fprintf(stderr,
                "Coordinates are out of range or calculation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.3f km\n", distance_km) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}