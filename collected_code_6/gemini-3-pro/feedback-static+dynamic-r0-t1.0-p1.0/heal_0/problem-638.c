#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_wind_chill(double temperature, double wind_speed);

double calculate_wind_chill(double temperature, double wind_speed) {
    if (temperature > 50.0 || wind_speed <= 3.0) {
        return temperature;
    }
    return 35.74 + (0.6215 * temperature) - (35.75 * pow(wind_speed, 0.16)) + (0.4275 * temperature * pow(wind_speed, 0.16));
}

int main(void) {
    double temperature;
    double wind_speed;
    double wind_chill;

    if (scanf("%lf %lf", &temperature, &wind_speed) != 2) {
        fprintf(stderr, "Invalid input format.\n");
        return EXIT_FAILURE;
    }

    if (wind_speed < 0.0) {
        fprintf(stderr, "Wind speed cannot be negative.\n");
        return EXIT_FAILURE;
    }

    wind_chill = calculate_wind_chill(temperature, wind_speed);
    
    if (printf("%.2f\n", wind_chill) < 0) {
        fprintf(stderr, "Output error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}