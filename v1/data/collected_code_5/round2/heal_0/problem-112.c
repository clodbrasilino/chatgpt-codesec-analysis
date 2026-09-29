#include <stdio.h>
#include <math.h>

double calculatePerimeter(double radius, double height) {
    if(radius <= 0 || height <= 0) {
        printf("Error: Invalid radius or height. Both must be positive values.\n");
        return -1;
    }
    double perimeter = 2 * M_PI * radius * (radius + height);
    return perimeter;
}

int main() {
    double radius, height;
    printf("Enter radius of the cylinder: ");
    if(scanf("%lf", &radius) != 1) {
        printf("Error: Invalid input.\n");
        return -1;
    }
    printf("Enter height of the cylinder: ");
    if(scanf("%lf", &height) != 1) {
        printf("Error: Invalid input.\n");
        return -1;
    }
    double perimeter = calculatePerimeter(radius, height);
    if(perimeter != -1) {
        printf("Perimeter of the cylinder is: %.2lf\n", perimeter);
    }
    return 0;
}