#include <stdio.h>
#include <math.h>

double surface_area(double radius) {
    return M_PI * radius * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }
    printf("The top or bottom surface area of the cylinder is: %.2f\n", surface_area(radius));
    return 0;
}