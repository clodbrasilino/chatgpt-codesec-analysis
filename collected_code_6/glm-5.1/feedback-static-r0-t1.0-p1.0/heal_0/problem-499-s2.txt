#include <stdio.h>
#include <math.h>

double calculate_diameter(double radius) {
    if (isnan(radius) || isinf(radius) || radius < 0.0) {
        return NAN;
    }
    return 2.0 * radius;
}

int main(void) {
    double radius = 5.0;
    double diameter = calculate_diameter(radius);
    if (isnan(diameter)) {
        return 1;
    }
    printf("%f\n", diameter);
    return 0;
}