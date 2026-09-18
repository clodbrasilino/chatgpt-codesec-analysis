#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    }
    return false;
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("False\n");
        return 0;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}