#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef enum {
    SLOPE_OK,
    SLOPE_INVALID_INPUT,
    SLOPE_VERTICAL
} SlopeResult;

SlopeResult calculate_slope(const Point *p1, const Point *p2, double *slope) {
    if (p1 == NULL || p2 == NULL || slope == NULL) {
        return SLOPE_INVALID_INPUT;
    }

    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;

    if (fabs(dx) < 1e-12) {
        return SLOPE_VERTICAL;
    }

    if (fabs(dy) < 1e-12) {
        *slope = 0.0;
        return SLOPE_OK;
    }

    if (!isfinite(dx) || !isfinite(dy)) {
        return SLOPE_INVALID_INPUT;
    }

    *slope = dy / dx;

    if (!isfinite(*slope)) {
        return SLOPE_INVALID_INPUT;
    }

    return SLOPE_OK;
}

int main(void) {
    Point p1, p2;
    double slope;
    SlopeResult result;

    printf("Enter coordinates of first point (x y): ");
    if (scanf("%lf %lf", &p1.x, &p1.y) != 2) {
        fprintf(stderr, "Error reading first point coordinates\n");
        return EXIT_FAILURE;
    }

    printf("Enter coordinates of second point (x y): ");
    if (scanf("%lf %lf", &p2.x, &p2.y) != 2) {
        fprintf(stderr, "Error reading second point coordinates\n");
        return EXIT_FAILURE;
    }

    result = calculate_slope(&p1, &p2, &slope);

    switch (result) {
        case SLOPE_OK:
            printf("Slope: %.6f\n", slope);
            break;
        case SLOPE_VERTICAL:
            printf("The line is vertical (undefined slope)\n");
            break;
        case SLOPE_INVALID_INPUT:
            fprintf(stderr, "Invalid input or calculation error\n");
            return EXIT_FAILURE;
        default:
            fprintf(stderr, "Unknown error\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}