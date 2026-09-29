#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN_WIND_SPEED 3.0
#define MAX_TEMPERATURE 50.0

static int calculate_wind_chill(double temperature, double wind_speed, double *result);

static int calculate_wind_chill(double temperature, double wind_speed, double *result)
{
    double wind_factor;

    if (result == NULL) {
        return -1;
    }

    if (temperature > MAX_TEMPERATURE) {
        return -1;
    }

    if (wind_speed < MIN_WIND_SPEED) {
        return -1;
    }

    wind_factor = pow(wind_speed, 0.16);
    *result = 35.74 + (0.6215 * temperature)
              - (35.75 * wind_factor)
              + (0.4275 * temperature * wind_factor);

    if (isnan(*result) || isinf(*result)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double temperature = 0.0;
    double wind_speed = 0.0;
    double wind_chill = 0.0;
    int status;

    printf("Enter temperature in Fahrenheit (must be <= %.1f): ", MAX_TEMPERATURE);
    if (scanf("%lf", &temperature) != 1) {
        fprintf(stderr, "Error: invalid temperature input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter wind speed in mph (must be >= %.1f): ", MIN_WIND_SPEED);
    if (scanf("%lf", &wind_speed) != 1) {
        fprintf(stderr, "Error: invalid wind speed input.\n");
        return EXIT_FAILURE;
    }

    status = calculate_wind_chill(temperature, wind_speed, &wind_chill);
    if (status != 0) {
        fprintf(stderr, "Error: inputs out of valid range for wind chill calculation.\n");
        return EXIT_FAILURE;
    }

    printf("Wind chill index: %.2f F\n", wind_chill);

    return EXIT_SUCCESS;
}