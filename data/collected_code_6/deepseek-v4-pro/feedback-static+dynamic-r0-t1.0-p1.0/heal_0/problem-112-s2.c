#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_perimeter(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return 2.0 * (2.0 * M_PI * radius + height);
}

int main(void) {
    double radius, height;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    double result = cylinder_perimeter(radius, height);
    
    if (result < 0) {
        fprintf(stderr, "Dimensions must be non-negative\n");
        return 1;
    }
    
    printf("Perimeter of cylinder: %.2f\n", result);
    
    return 0;
}