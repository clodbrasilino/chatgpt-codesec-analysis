#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 600, got 70
  *  test case 0 failed: expected 400, got 60
  *  test case 2 failed: expected 144, got 34
  */

double parallelogram_perimeter(double base, double side) {
    return 2.0 * (base + side);
}

int main(void) {
    double base = 5.0;
    double side = 3.0;
    double perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    return 0;
}