#include <stdio.h>
#include <math.h>

float areaOfPentagon(float side) {
    return (sqrt(5 * (5 + 2 * sqrt(5))) * pow(side, 2)) / 4;
}

int main() {
    float side;
  
    printf("Enter the length of a side of the pentagon: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &side);
  
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    printf("Area of the pentagon: %f\n", areaOfPentagon(side));
  
    return 0;
}