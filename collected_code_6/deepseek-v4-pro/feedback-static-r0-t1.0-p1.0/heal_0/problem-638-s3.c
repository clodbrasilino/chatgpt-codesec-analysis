#include <stdio.h>
#include <math.h>

double calculate_wind_chill(double temperature_f, double wind_speed_mph) {
    if (temperature_f > 50.0 || wind_speed_mph < 3.0) {
        return temperature_f;
    }
    
    return 35.74 + 0.6215 * temperature_f 
           - 35.75 * pow(wind_speed_mph, 0.16)
           + 0.4275 * temperature_f * pow(wind_speed_mph, 0.16);
}

int main(void) {
    double temperature = 32.0;
    double wind_speed = 20.0;
    double wind_chill = calculate_wind_chill(temperature, wind_speed);
    
    printf("Wind Chill: %.2f F\n", wind_chill);
    
    return 0;
}