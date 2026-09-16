#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_isosceles(double a, double b, double c)
{
    const double scale = fmax(a, fmax(b, c));
    const double tolerance = 1e-9 * scale;

    return fabs(a - b) <= tolerance ||
           fabs(a - c) <= tolerance ||
           fabs(b - c) <= tolerance;
}

int main(void)
{
    double a;
    double b;
    double c;

    printf("Enter the three side lengths: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        fprintf(stderr, "Side lengths must be positive finite numbers.\n");
        return 1;
    }

    if (a > b + c || b > a + c || c > a + b ||
        fabs(a - (b + c)) <= 1e-9 * fmax(a, b + c) ||
        fabs(b - (a + c)) <= 1e-9 * fmax(b, a + c) ||
        fabs(c - (a + b)) <= 1e-9 * fmax(c, a + b)) {
        fprintf(stderr, "The side lengths do not form a valid triangle.\n");
        return 1;
    }

    if (is_isosceles(a, b, c)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return 0;
}