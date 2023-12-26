#include <stdio.h>
#include <math.h>

// Function to calculate surface area of a square pyramid
double surfaceAreaOfSquarePyramid(double sideLength, double height) {
    double baseArea = pow(sideLength, 2);
    double lateralArea = 2 * sideLength * sqrt(pow(sideLength / 2, 2) + pow(height, 2));
    double surfaceArea = baseArea + lateralArea;

    return surfaceArea;
}

int main() {
    double sideLength, height;
    printf("Enter the side length of the square pyramid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sideLength' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &sideLength);
    printf("Enter the height of the square pyramid: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &height);

    /* Possible weaknesses found:
     *  Cannot determine that 'sideLength' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    double area = surfaceAreaOfSquarePyramid(sideLength, height);
    printf("The surface area of the square pyramid is: %.2lf\n", area);

    return 0;
}