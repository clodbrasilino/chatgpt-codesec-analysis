#include <stdio.h>

double square_perimeter(double side);

int main(void) {
    double side;
    printf("Enter the side length of the square: ");
    if (scanf("%lf", &side) != 1 || side < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative number.\n");
        return 1;
    }
    printf("Perimeter: %.2f\n", square_perimeter(side));
    return 0;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 16, got <no output>
  *  test case 1 failed: expected 20, got <no output>
  *  test case 0 failed: expected 40, got <no output>
  */

double square_perimeter(double side) {
    return 4.0 * side;
}