#include <stdio.h>

double cube_volume(double side);

int main(void) {
    double side;
    printf("Enter the side length of the cube: ");
    if (scanf("%lf", &side) != 1 || side < 0) {
        printf("Invalid input. Side length must be a non-negative number.\n");
        return 1;
    }
    printf("Volume of the cube: %.2lf\n", cube_volume(side));
    return 0;
}

double cube_volume(double side) {
    return side * side * side;
}