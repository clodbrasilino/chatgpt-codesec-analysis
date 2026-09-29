#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

int is_valid_triangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b > c && a + c > b && b + c > a) {
        return 1;
    }
    return 0;
}

int main(void) {
    double side1, side2, side3;

    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (is_valid_triangle(side1, side2, side3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}