#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 600, got 70
  *  test case 0 failed: expected 400, got 60
  *  test case 2 failed: expected 144, got 34
  */

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