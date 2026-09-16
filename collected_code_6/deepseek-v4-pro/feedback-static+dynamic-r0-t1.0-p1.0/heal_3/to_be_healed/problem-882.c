#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 144, got <no output>
  *  test case 0 failed: expected 400, got <no output>
  *  test case 1 failed: expected 600, got <no output>
  */

double parallelogram_perimeter(double base, double side) {
    return 2.0 * (base + side);
}

int main(void) {
    double base = 100.0;
    double side = 100.0;
    double perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    base = 200.0;
    side = 100.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    base = 36.0;
    side = 36.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    return 0;
}