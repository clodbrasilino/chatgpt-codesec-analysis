#include <math.h>
#include <stdbool.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return false;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    }

    if (b > c) {
        double temp = b;
        b = c;
        c = temp;
    }

    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    }

    return a > c - b;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(is_valid_triangle(a, b, c) ? "Valid triangle" : "Invalid triangle");
    return 0;
}