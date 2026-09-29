#include <stdio.h>
#include <math.h>

double calculate_circumference(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius;
}

int main(void) {
    double radius;
    
    if (scanf("%lf", &radius) != 1) {
        return 1;
    }
    
    double circumference = calculate_circumference(radius);
    
    if (circumference < 0.0) {
        return 1;
    }
    
    printf("%f\n", circumference);
    
    return 0;
}