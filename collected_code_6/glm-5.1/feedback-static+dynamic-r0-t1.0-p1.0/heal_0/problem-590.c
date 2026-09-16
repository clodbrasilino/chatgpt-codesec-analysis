#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Rectangular;

typedef struct {
    double r;
    double theta;
} Polar;

int polar_to_rectangular(Polar p, Rectangular *result) {
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (p.r < 0.0) {
        return EXIT_FAILURE;
    }

    if (!isfinite(p.r) || !isfinite(p.theta)) {
        return EXIT_FAILURE;
    }

    result->x = p.r * cos(p.theta);
    result->y = p.r * sin(p.theta);

    return EXIT_SUCCESS;
}

int main(void) {
    Polar p;
    Rectangular r;

    p.r = 1.0;
    p.theta = M_PI / 4.0;

    if (polar_to_rectangular(p, &r) == EXIT_SUCCESS) {
        printf("x: %f, y: %f\n", r.x, r.y);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}