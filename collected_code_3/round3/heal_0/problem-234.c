#include <stdio.h>

double cubeVolume(double side) {
    return side * side * side;
}

int main() {
    double side;
    printf("Enter the side of the cube: ");
    scanf("%lf", &side);
    printf("Volume of the cube: %.2lf\n", cubeVolume(side));
    return 0;
}