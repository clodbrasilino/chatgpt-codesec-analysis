#include <stdio.h>
#include <math.h>

double sphere_volume(double radius) {
    return (4.0 / 3.0) * M_PI * radius * radius * radius;
}

int main(void) {
    double radius;
    if (scanf("%lf", &radius) != 1) {
        return 1;
    }
    if (radius < 0.0) {
        return 1;
    }
    printf("%.6f\n", sphere_volume(radius));
    return 0;
}