#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

float calculate_wind_chill_index(float temperature, float wind_speed) {
    float wind_chill_index;
    
    /* Possible weaknesses found:
     *  include '<math.h>' or provide a declaration of 'pow'
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'pow' [-Wbuiltin-declaration-mismatch]
     */
    wind_chill_index = 35.74 + 0.6215 * temperature - 35.75 * pow(wind_speed, 0.16) + 0.4275 * temperature * pow(wind_speed, 0.16);
    
    return wind_chill_index;
}

int main() {
    float temperature, wind_speed;
    
    printf("Enter the temperature (in degrees Fahrenheit): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'temperature' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &temperature);
    
    printf("Enter the wind speed (in miles per hour): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'wind_speed' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &wind_speed);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'wind_speed' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'temperature' is initialized [premium-bughuntingUninit]
     */
    float wind_chill_index = calculate_wind_chill_index(temperature, wind_speed);
    printf("The Wind Chill Index is: %.2f", wind_chill_index);
    
    return 0;
}