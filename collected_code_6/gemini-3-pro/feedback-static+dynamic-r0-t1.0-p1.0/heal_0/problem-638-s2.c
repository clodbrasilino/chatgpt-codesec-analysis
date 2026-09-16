#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculate_wind_chill(double temperature, double wind_speed);

double calculate_wind_chill(double temperature, double wind_speed) {
    if (temperature > 10.0 || wind_speed <= 4.8) {
        return temperature;
    }
    return 13.12 + 0.6215 * temperature - 11.37 * pow(wind_speed, 0.16) + 0.3965 * temperature * pow(wind_speed, 0.16);
}

int main(void) {
    double temperature = 0.0;
    double wind_speed = 0.0;
    double wind_chill = 0.0;
    int read_status = 0;

    read_status = scanf("%lf %lf", &temperature, &wind_speed);

    if (read_status != 2) {
        return EXIT_FAILURE;
    }

    if (wind_speed < 0.0) {
        return EXIT_FAILURE;
    }

    wind_chill = calculate_wind_chill(temperature, wind_speed);

    if (printf("%.2f\n", wind_chill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}