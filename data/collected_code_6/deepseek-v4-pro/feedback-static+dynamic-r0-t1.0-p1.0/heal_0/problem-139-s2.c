#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double circumference(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius;
}

int main(void) {
    double radius;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (radius < 0.0) {
        printf("Radius cannot be negative\n");
        return 1;
    }
    
    printf("Circumference: %.6f\n", circumference(radius));
    
    return 0;
}