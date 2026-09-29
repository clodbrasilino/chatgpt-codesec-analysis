#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double longest;
    double x;
    double y;

    if (a >= b && a >= c) {
        longest = a;
        x = b;
        y = c;
    } else if (b >= a && b >= c) {
        longest = b;
        x = a;
        y = c;
    } else {
        longest = c;
        x = a;
        y = b;
    }

    return x > longest - y;
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

    printf("%d\n", is_valid_triangle(a, b, c) ? 1 : 0);
    return 0;
}