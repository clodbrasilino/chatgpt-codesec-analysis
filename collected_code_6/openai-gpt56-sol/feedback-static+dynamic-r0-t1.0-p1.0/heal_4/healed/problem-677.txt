#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double largest = fmax(a, fmax(b, c));
    double sum = a + b + c;

    if (!isfinite(sum)) {
        double x;
        double y;

        if (largest == a) {
            x = b;
            y = c;
        } else if (largest == b) {
            x = a;
            y = c;
        } else {
            x = a;
            y = b;
        }

        return x / largest + y / largest > 1.0;
    }

    double other_sum = sum - largest;
    double tolerance = DBL_EPSILON * fmax(sum, 1.0);

    return other_sum - largest > tolerance;
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