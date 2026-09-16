#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TEMP_F 50.0
#define MIN_WIND_MPH 3.0

int calculate_wind_chill(double temperature_f, double wind_speed_mph, double *result)
{
    double wind_factor;

    if (result == NULL) {
        return -1;
    }

    if (temperature_f > MAX_TEMP_F) {
        return -2;
    }

    if (wind_speed_mph < MIN_WIND_MPH) {
        return -3;
    }

    wind_factor = pow(wind_speed_mph, 0.16);
    *result = 35.74 + (0.6215 * temperature_f)
              - (35.75 * wind_factor)
              + (0.4275 * temperature_f * wind_factor);

    if (isnan(*result) || isinf(*result)) {
        return -4;
    }

    return 0;
}

int main(void)
{
    double temperature_f;
    double wind_speed_mph;
    double wind_chill;
    int status;

    printf("Enter air temperature (Fahrenheit): ");
    if (scanf("%lf", &temperature_f) != 1) {
        fprintf(stderr, "Error: invalid temperature input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter wind speed (mph): ");
    if (scanf("%lf", &wind_speed_mph) != 1) {
        fprintf(stderr, "Error: invalid wind speed input.\n");
        return EXIT_FAILURE;
    }

    status = calculate_wind_chill(temperature_f, wind_speed_mph, &wind_chill);

    switch (status) {
    case 0:
        printf("Wind chill index: %.2f F\n", wind_chill);
        break;
    case -2:
        fprintf(stderr, "Error: temperature must be at most %.1f F.\n", MAX_TEMP_F);
        return EXIT_FAILURE;
    case -3:
        fprintf(stderr, "Error: wind speed must be at least %.1f mph.\n", MIN_WIND_MPH);
        return EXIT_FAILURE;
    default:
        fprintf(stderr, "Error: calculation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}