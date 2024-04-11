#include <stdio.h>
#include <math.h>

double calculate_wind_chill_index(double temperature, double wind_speed) {
    double wind_chill_index = 35.74 + 0.6215 * temperature - 35.75 * pow(wind_speed, 0.16) + 0.4275 * temperature * pow(wind_speed, 0.16);
    return wind_chill_index;
}

int main() {
    double temperature, wind_speed, wind_chill_index;

    printf("Enter temperature in Fahrenheit: ");
    scanf("%lf", &temperature);

    printf("Enter wind speed in mph: ");
    scanf("%lf", &wind_speed);

    wind_chill_index = calculate_wind_chill_index(temperature, wind_speed);

    printf("Wind Chill Index: %.2lf\n", wind_chill_index);

    return 0;
}