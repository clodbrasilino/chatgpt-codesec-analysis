#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return false;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    const double largest = fmax(a, fmax(b, c));
    const double sum = a + b + c;

    return isfinite(sum) && (sum - largest > largest);
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(a, b, c)) {
        puts("Valid triangle");
    } else {
        puts("Invalid triangle");
    }

    return EXIT_SUCCESS;
}