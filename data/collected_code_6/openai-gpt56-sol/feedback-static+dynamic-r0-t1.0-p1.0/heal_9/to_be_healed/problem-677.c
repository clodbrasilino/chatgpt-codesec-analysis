#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double largest = fmax(a, fmax(b, c));
    double sum = a + b + c - largest;

    if (isinf(sum)) {
        return true;
    }

    double tolerance = DBL_EPSILON * fmax(largest, sum) * 4.0;

    return sum > largest + tolerance;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%s\n", is_valid_triangle(a, b, c) ? "Valid" : "Invalid");
    return 0;
}