#include <stdio.h>

double cubeVolume(double side) {
    return side * side * side;
}

int main() {
    double side;
    printf("Enter the side of the cube: ");
    scanf("%lf", &side);
    printf("The volume of the cube is: %.2lf\n", cubeVolume(side));
    return 0;
}