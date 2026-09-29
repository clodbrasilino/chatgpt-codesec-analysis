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
    double smallest = fmin(a, fmin(b, c));
    double middle = a + b + c - largest - smallest;

    if (!isfinite(middle)) {
        if (largest == a) {
            middle = fmax(b, c);
            smallest = fmin(b, c);
        } else if (largest == b) {
            middle = fmax(a, c);
            smallest = fmin(a, c);
        } else {
            middle = fmax(a, b);
            smallest = fmin(a, b);
        }
    }

    return largest - middle < smallest;
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