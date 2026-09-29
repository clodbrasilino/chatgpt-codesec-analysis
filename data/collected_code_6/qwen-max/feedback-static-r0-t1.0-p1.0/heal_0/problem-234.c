#include <stdio.h>

double volume_of_cube(double side_length) {
    return side_length * side_length * side_length;
}

int main() {
    double side_length;
    printf("Enter the side length of the cube: ");
    if (scanf("%lf", &side_length) != 1 || side_length < 0.0) {
        printf("Invalid input. Please enter a non-negative number.\n");
        return 1;
    }
    double volume = volume_of_cube(side_length);
    printf("Volume of the cube: %f\n", volume);
    return 0;
}