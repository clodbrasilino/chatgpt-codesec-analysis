#include <stdio.h>

double parallelogram_perimeter(double base, double side) {
    return 2.0 * base + 2.0 * side;
}

int main(void) {
    double base, side, perimeter;

    base = 100.0;
    side = 100.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("%.2f\n", perimeter);

    base = 200.0;
    side = 100.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("%.2f\n", perimeter);

    base = 36.0;
    side = 36.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("%.2f\n", perimeter);

    return 0;
}