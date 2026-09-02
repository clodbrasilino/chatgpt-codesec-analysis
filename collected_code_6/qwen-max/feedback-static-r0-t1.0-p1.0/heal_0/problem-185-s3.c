#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

Point findFocus(double a, double b, double c) {
    double p = 1.0 / (4 * a);
    double focusX = -b / (2 * a);
    double focusY = c - (b * b + 1) / (4 * a);
    Point focus = {focusX, focusY + p};
    return focus;
}

int main() {
    double a, b, c;
    printf("Enter the coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    if (a == 0) {
        fprintf(stderr, "Error: Coefficient 'a' must not be zero\n");
        return EXIT_FAILURE;
    }

    Point focus = findFocus(a, b, c);
    printf("The focus of the parabola is at: (%.2f, %.2f)\n", focus.x, focus.y);

    return EXIT_SUCCESS;
}