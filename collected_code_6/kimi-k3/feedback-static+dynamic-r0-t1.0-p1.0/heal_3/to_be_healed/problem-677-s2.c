#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool is_valid_triangle(double a, double b, double c) {
    if (isnan(a) || isnan(b) || isnan(c)) {
        return false;
    }
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if (a > DBL_MAX - b || a > DBL_MAX - c || b > DBL_MAX - c) {
        return false;
    }
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main(void) {
    double a, b, c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 0;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}