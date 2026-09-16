#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

int is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return 1;
    }
    return 0;
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}