#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_perimeter(double radius, double height) {
    if (radius <= 0 || height <= 0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius + 2.0 * height;
}

int main(void) {
    double radius, height;
    
    printf("Enter radius: ");
    scanf("%lf", &radius);
    
    printf("Enter height: ");
    scanf("%lf", &height);
    
    double perimeter = cylinder_perimeter(radius, height);
    
    if (perimeter < 0) {
        printf("Invalid input. Radius and height must be positive.\n");
        return 1;
    }
    
    printf("Perimeter of cylinder: %.2f\n", perimeter);
    
    return 0;
}