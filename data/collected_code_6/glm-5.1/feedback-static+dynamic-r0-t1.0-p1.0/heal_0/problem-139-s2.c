#include <stdio.h>
#include <math.h>

double calculate_circumference(double radius) {
    if (radius < 0.0) {
        return NAN;
    }
    return 2.0 * M_PI * radius;
}

int main(void) {
    double radius = 5.0;
    double circumference = calculate_circumference(radius);
    
    if (isnan(circumference)) {
        fprintf(stderr, "Invalid radius provided.\n");
        return 1;
    }
    
    printf("%f\n", circumference);
    return 0;
}