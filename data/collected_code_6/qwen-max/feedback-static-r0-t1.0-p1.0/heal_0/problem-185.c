#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

Point findFocus(double a, double b, double c) {
    double x = -b / (2 * a);
    double y = (1 + 4 * a * c - b * b) / (4 * a);
    Point focus = {x, y + 1.0 / (4 * a)};
    return focus;
}

int main() {
    double a, b, c;
    printf("Enter the coefficients a, b, and c: ");
    int result = scanf("%lf %lf %lf", &a, &b, &c);
    if (result != 3 || a == 0) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    Point focus = findFocus(a, b, c);
    printf("The focus of the parabola is at: (%.2f, %.2f)\n", focus.x, focus.y);
    return EXIT_SUCCESS;
}