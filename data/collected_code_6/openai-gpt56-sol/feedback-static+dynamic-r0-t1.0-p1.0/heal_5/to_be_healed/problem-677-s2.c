#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool sum_greater_than(double x, double y, double z)
{
    return x > z - y;
}
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

    return sum_greater_than(a, b, c) &&
           sum_greater_than(a, c, b) &&
           sum_greater_than(b, c, a);
}

int main(void)
{
    double a;
    double b;
    double c;
    char extra;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 ||
        scanf(" %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(is_valid_triangle(a, b, c) ? "Valid triangle" : "Invalid triangle");
    return 0;
}