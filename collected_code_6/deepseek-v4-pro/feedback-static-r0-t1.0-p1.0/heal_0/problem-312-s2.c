#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double cone_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return (PI * radius * radius * height) / 3.0;
}

int main(void) {
    double radius, height, volume;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height\n");
        return EXIT_FAILURE;
    }
    
    volume = cone_volume(radius, height);
    printf("Volume of cone: %.6f\n", volume);
    
    return EXIT_SUCCESS;
}