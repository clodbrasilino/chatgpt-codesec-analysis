#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double cone_surface_area(double radius, double height) {
    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    double slant_height = sqrt(radius * radius + height * height);
    return PI * radius * (radius + slant_height);
}

int main(void) {
    double radius, height;
    
    printf("Enter radius of cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter height of cone: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height\n");
        return EXIT_FAILURE;
    }
    
    double area = cone_surface_area(radius, height);
    printf("Surface area of cone: %.2f\n", area);
    
    return 0;
}