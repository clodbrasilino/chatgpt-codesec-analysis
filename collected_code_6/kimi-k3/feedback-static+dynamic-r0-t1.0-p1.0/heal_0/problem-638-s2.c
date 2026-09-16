#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_wind_chill(double temperature, double wind_speed) {
    return 13.12 + 0.6215 * temperature - 11.37 * pow(wind_speed, 0.16) + 0.3965 * temperature * pow(wind_speed, 0.16);
}

int main(void) {
    double temperature;
    double wind_speed;
    
    printf("Enter temperature in Celsius: ");
    if (scanf("%lf", &temperature) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter wind speed in km/h: ");
    if (scanf("%lf", &wind_speed) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (wind_speed < 0.0) {
        fprintf(stderr, "Wind speed cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    double wind_chill = calculate_wind_chill(temperature, wind_speed);
    printf("Wind chill index: %.2f\n", wind_chill);
    
    return EXIT_SUCCESS;
}