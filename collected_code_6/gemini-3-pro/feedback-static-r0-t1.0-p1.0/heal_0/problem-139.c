#include <stdio.h>

#define PI 3.14159265358979323846

double calculate_circumference(double radius);

double calculate_circumference(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius;
}

int main(void) {
    double radius = 0.0;
    double circumference = 0.0;

    if (scanf("%lf", &radius) != 1) {
        return 1;
    }

    circumference = calculate_circumference(radius);

    if (circumference < 0.0) {
        return 1;
    }

    if (printf("%.6f\n", circumference) < 0) {
        return 1;
    }

    return 0;
}