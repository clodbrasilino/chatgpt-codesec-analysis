#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_directrix(double a, double b, double c, double *directrix) {
    double discriminant;
    double vertex_y;
    double p;

    if (directrix == NULL) {
        return -1;
    }

    if (a == 0.0) {
        *directrix = (a == 0.0 && b == 0.0) ? c : NAN;
        return -1;
    }

    discriminant = (b * b) - (4.0 * a * c);

    if (discriminant < 0.0 && fabs(discriminant) > 1e-12) {
        *directrix = NAN;
        return -1;
    }

    vertex_y = -discriminant / (4.0 * a);
    p = 1.0 / (4.0 * a);
    *directrix = vertex_y - p;

    return 0;
}

int main(void) {
    double a, b, c;
    double directrix;
    int status;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }

    status = find_directrix(a, b, c, &directrix);

    if (status == 0) {
        printf("%lf\n", directrix);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}