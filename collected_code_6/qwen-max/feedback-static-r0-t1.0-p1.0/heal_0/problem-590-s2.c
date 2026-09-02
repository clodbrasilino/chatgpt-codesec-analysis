#include <stdio.h>
#include <math.h>

void polar_to_rectangular(double r, double theta, double *x, double *y) {
    *x = r * cos(theta);
    *y = r * sin(theta);
}

int main() {
    double r = 5.0;
    double theta = M_PI / 4; // 45 degrees in radians
    double x, y;

    polar_to_rectangular(r, theta, &x, &y);

    printf("Rectangular coordinates: (%f, %f)\n", x, y);

    return 0;
}