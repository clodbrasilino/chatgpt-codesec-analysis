#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_wind_chill(double temperature, double wind_speed) {
    if (wind_speed < 0.0) {
        return NAN;
    }
    if (wind_speed == 0.0) {
        return temperature;
    }
    double v_pow = pow(wind_speed, 0.16);
    double wci = 13.12 + 0.6215 * temperature - 11.37 * v_pow + 0.3965 * temperature * v_pow;
    return wci;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <temperature_c> <wind_speed_kph>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    double temperature = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid temperature input\n");
        return EXIT_FAILURE;
    }
    double wind_speed = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid wind speed input\n");
        return EXIT_FAILURE;
    }
    double wci = calculate_wind_chill(temperature, wind_speed);
    if (isnan(wci)) {
        fprintf(stderr, "Wind speed cannot be negative\n");
        return EXIT_FAILURE;
    }
    printf("%.2f\n", wci);
    return EXIT_SUCCESS;
}