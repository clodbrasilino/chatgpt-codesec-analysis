#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return false;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    return a > fabs(b - c) && a <= b + c && a < b + c;
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