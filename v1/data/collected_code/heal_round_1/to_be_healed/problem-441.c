#include <stdio.h>

double surfaceAreaOfCube(double side) {
    return 6 * side * side;
}

int main() {
    double side;
    printf("Enter the side length of the cube: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &side);
    /* Possible weaknesses found:
     *  Cannot determine that 'side' is initialized [premium-bughuntingUninit]
     */
    double surfaceArea = surfaceAreaOfCube(side);
    printf("The surface area of the cube is: %.2lf", surfaceArea);

    return 0;
}