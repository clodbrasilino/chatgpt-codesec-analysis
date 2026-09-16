#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_wind_chill(double temperature_f,
                                double wind_speed_mph,
                                double *wind_chill_f)
{
    double wind_factor;
    double result;

    if (wind_chill_f == NULL ||
        !isfinite(temperature_f) ||
        !isfinite(wind_speed_mph) ||
        temperature_f > 50.0 ||
        wind_speed_mph < 3.0) {
        return -1;
    }

    wind_factor = pow(wind_speed_mph, 0.16);
    result = 35.74
           + 0.6215 * temperature_f
           - 35.75 * wind_factor
           + 0.4275 * temperature_f * wind_factor;

    if (!isfinite(result)) {
        return -1;
    }

    *wind_chill_f = result;
    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *const argv[])
{
    double temperature_f;
    double wind_speed_mph;
    double wind_chill_f;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <temperature_F> <wind_speed_mph>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &temperature_f) != 0 ||
        parse_double(argv[2], &wind_speed_mph) != 0) {
        fprintf(stderr, "Error: arguments must be finite numbers.\n");
        return EXIT_FAILURE;
    }

    if (calculate_wind_chill(temperature_f,
                             wind_speed_mph,
                             &wind_chill_f) != 0) {
        fprintf(stderr,
                "Error: temperature must be at most 50 F and wind speed "
                "must be at least 3 mph.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.2f F\n", wind_chill_f) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}