#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tetrahedron_volume(double a, double b, double c, double d, double e, double f) {
    if (a <= 0 || b <= 0 || c <= 0 || d <= 0 || e <= 0 || f <= 0) {
        return -1.0;
    }

    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    double d2 = d * d;
    double e2 = e * e;
    double f2 = f * f;

    double term1 = a2 * d2 * (b2 + c2 + e2 + f2 - a2 - d2);
    double term2 = b2 * e2 * (a2 + c2 + d2 + f2 - b2 - e2);
    double term3 = c2 * f2 * (a2 + b2 + d2 + e2 - c2 - f2);
    double term4 = a2 * b2 * c2;
    double term5 = a2 * e2 * f2;
    double term6 = b2 * d2 * f2;
    double term7 = c2 * d2 * e2;

    double sum = term1 + term2 + term3 - term4 - term5 - term6 - term7;

    if (sum <= 0.0) {
        return -1.0;
    }

    return sqrt(sum) / 12.0;
}

int main(void) {
    double a, b, c, d, e, f;
    
    printf("Enter the six edge lengths of the tetrahedron:\n");
    printf("Opposite edges: (a,d), (b,e), (c,f)\n");
    
    if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != 6) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double volume = tetrahedron_volume(a, b, c, d, e, f);
    
    if (volume < 0.0) {
        fprintf(stderr, "Invalid edge lengths\n");
        return EXIT_FAILURE;
    }

    printf("Volume: %.6f\n", volume);
    return EXIT_SUCCESS;
}