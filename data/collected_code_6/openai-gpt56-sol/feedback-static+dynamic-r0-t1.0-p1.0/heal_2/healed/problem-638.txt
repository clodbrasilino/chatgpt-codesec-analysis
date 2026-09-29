#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_wind_chill(double temperature_f, double wind_speed_mph,
                                double *wind_chill_f)
{
    if (wind_chill_f == NULL ||
        !isfinite(temperature_f) ||
        !isfinite(wind_speed_mph) ||
        wind_speed_mph < 0.0) {
        return -1;
    }

    if (temperature_f > 50.0 || wind_speed_mph < 3.0) {
        *wind_chill_f = temperature_f;
        return 0;
    }

    const double speed_factor = pow(wind_speed_mph, 0.16);

    if (!isfinite(speed_factor)) {
        return -1;
    }

    const double result = 35.74 + (0.6215 * temperature_f) -
                          (35.75 * speed_factor) +
                          (0.4275 * temperature_f * speed_factor);

    if (!isfinite(result)) {
        return -1;
    }

    *wind_chill_f = result;
    return 0;
}

static int parse_double(const char *text, double *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    char *end = NULL;
    errno = 0;

    const double parsed = strtod(text, &end);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <temperature_F> <wind_speed_mph>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    double temperature_f;
    double wind_speed_mph;
    double wind_chill_f;

    if (parse_double(argv[1], &temperature_f) != 0 ||
        parse_double(argv[2], &wind_speed_mph) != 0) {
        fputs("Error: inputs must be finite numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_wind_chill(temperature_f, wind_speed_mph,
                             &wind_chill_f) != 0) {
        fputs("Error: unable to calculate wind chill.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", wind_chill_f) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}