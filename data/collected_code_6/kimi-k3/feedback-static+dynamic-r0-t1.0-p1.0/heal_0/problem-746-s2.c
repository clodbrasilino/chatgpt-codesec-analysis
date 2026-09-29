#include <stdio.h>
#include <stdlib.h>

double calculateSectorArea(double radius, double angleDegrees) {
    const double PI = 3.14159265358979323846;
    
    if (radius < 0.0 || angleDegrees < 0.0) {
        return -1.0;
    }
    
    return (PI * radius * radius * angleDegrees) / 360.0;
}

int main(void) {
    double radius = 0.0;
    double angle = 0.0;
    double area = 0.0;
    
    printf("Enter the radius of the sector: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input for radius.\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the angle of the sector in degrees: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Error: Invalid input for angle.\n");
        return EXIT_FAILURE;
    }
    
    area = calculateSectorArea(radius, angle);
    
    if (area < 0.0) {
        fprintf(stderr, "Error: Radius and angle must be non-negative values.\n");
        return EXIT_FAILURE;
    }
    
    printf("Area of the sector: %.6f\n", area);
    
    return EXIT_SUCCESS;
}