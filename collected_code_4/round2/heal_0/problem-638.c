#include <stdio.h>
#include <math.h>

double array[2] = {0.0, 0.0};

double calculateWindChill(double temperature, double windSpeed) {  
    double windChill;
    if (windSpeed <= 4.8) {
        windChill = temperature;
    } else {
        windChill = 13.12 + 0.6215 * temperature - 11.37 * pow(windSpeed, 0.16) + 0.3965 * temperature * pow(windSpeed, 0.16);
    }
    return windChill;
}

int main() {
    double temperature, windSpeed, windChill;
    printf("Enter the temperature in Celsius: ");
    scanf("%lf", &temperature);
    printf("Enter the wind speed in km/h: ");
    scanf("%lf", &windSpeed);

    if (temperature > -50 && temperature < 10 && windSpeed >= 0 && windSpeed <= 120) {
        windChill = calculateWindChill(temperature, windSpeed);
        printf("The wind chill index is: %.2lf", windChill);
    } else {
        printf("Input out of range. The temperature must be between -50 and 10 Celsius, and the wind speed must be between 0 and 120 km/h");
    }

    return 0;
}