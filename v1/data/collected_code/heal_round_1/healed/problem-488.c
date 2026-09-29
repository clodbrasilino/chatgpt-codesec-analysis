#include <stdio.h>
#include <math.h>

float areaOfPentagon(float side) {
    return (sqrt(5 * (5 + 2 * sqrt(5))) * pow(side, 2)) / 4;
}

int main() {
    float side = 0;

    printf("Enter the length of a side of the pentagon: ");
    scanf("%f", &side);

    float area = areaOfPentagon(side);
    
    printf("Area of the pentagon: %f\n", area);

    return 0;
}