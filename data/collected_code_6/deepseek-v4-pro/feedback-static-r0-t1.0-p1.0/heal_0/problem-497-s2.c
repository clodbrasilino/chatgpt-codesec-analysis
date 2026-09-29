#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double cone_surface_area(double radius, double height) {
    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: Radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    double slant_height = sqrt(radius * radius + height * height);
    return M_PI * radius * (radius + slant_height);
}

int main(void) {
    double radius, height;
    
    printf("Enter cone radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter cone height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }
    
    double area = cone_surface_area(radius, height);
    printf("Surface area of cone: %.2f\n", area);
    
    return EXIT_SUCCESS;
}