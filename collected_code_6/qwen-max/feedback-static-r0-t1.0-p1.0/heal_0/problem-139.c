#include <stdio.h>
#include <math.h>

double circumference(double radius) {
    return 2 * M_PI * radius;
}

int main() {
    double radius = 5.0;
    double result = circumference(radius);
    printf("Circumference: %f\n", result);
    return 0;
}