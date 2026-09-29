#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double calculate_wind_chill(double temperature, double wind_speed) {
    if (temperature > 10.0 || wind_speed <= 3.0) {
        return temperature;
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     */
    return 13.12 + 0.6215 * temperature - 11.37 * pow(wind_speed, 0.16) + 0.3965 * temperature * pow(wind_speed, 0.16);
}

int main() {
    double temperature, wind_speed, wind_chill;

    printf("Enter the temperature in Celsius: ");
    scanf("%lf", &temperature);

    printf("Enter the wind speed in km/h: ");
    scanf("%lf", &wind_speed);

    wind_chill = calculate_wind_chill(temperature, wind_speed);

    printf("Wind Chill Index: %.2f\n", wind_chill);

    return 0;
}