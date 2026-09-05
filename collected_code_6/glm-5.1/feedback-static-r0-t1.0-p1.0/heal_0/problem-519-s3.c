#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_tetrahedron_volume(double a, double b, double c, double d, double e, double f) {
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    double d2 = d * d;
    double e2 = e * e;
    double f2 = f * f;

    double val = 4.0 * a2 * b2 * c2 
               - a2 * (b2 + c2 - f2) * (b2 + c2 - f2) 
               - b2 * (a2 + c2 - e2) * (a2 + c2 - e2) 
               - c2 * (a2 + b2 - d2) * (a2 + b2 - d2) 
               + (a2 + b2 - d2) * (b2 + c2 - f2) * (a2 + c2 - e2);

    if (val <= 0.0) {
        return -1.0;
    }

    return sqrt(val) / 12.0;
}

int main(void) {
    double a, b, c, d, e, f;

    if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != 6) {
        return EXIT_FAILURE;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0 || d <= 0.0 || e <= 0.0 || f <= 0.0) {
        return EXIT_FAILURE;
    }

    double volume = calculate_tetrahedron_volume(a, b, c, d, e, f);

    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.4f\n", volume);

    return EXIT_SUCCESS;
}