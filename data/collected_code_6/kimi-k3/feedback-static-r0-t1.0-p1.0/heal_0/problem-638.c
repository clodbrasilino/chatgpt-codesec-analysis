#include <stdio.h>
#include <math.h>

double calculate_wind_chill(double temperature_f, double wind_speed_mph)
{
    if (temperature_f > 50.0 || wind_speed_mph < 3.0) {
        return temperature_f;
    }
    
    double wind_pow = pow(wind_speed_mph, 0.16);
    return 35.74 + (0.6215 * temperature_f) - (35.75 * wind_pow) + (0.4275 * temperature_f * wind_pow);
}

int main(void)
{
    double temperature_f;
    double wind_speed_mph;
    
    printf("Enter temperature in Fahrenheit: ");
    if (scanf("%lf", &temperature_f) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter wind speed in mph: ");
    if (scanf("%lf", &wind_speed_mph) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (wind_speed_mph < 0.0) {
        fprintf(stderr, "Wind speed cannot be negative\n");
        return 1;
    }
    
    double wind_chill = calculate_wind_chill(temperature_f, wind_speed_mph);
    printf("Wind chill index: %.2f°F\n", wind_chill);
    
    return 0;
}