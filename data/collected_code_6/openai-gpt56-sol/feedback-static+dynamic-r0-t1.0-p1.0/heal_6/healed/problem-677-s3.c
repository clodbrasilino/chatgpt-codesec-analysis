#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double longest = fmax(a, fmax(b, c));
    double sum = a + b + c - longest;

    if (!isfinite(sum)) {
        return true;
    }

    double difference = longest - sum;
    double tolerance = 4.0 * nextafter(longest, INFINITY) - 4.0 * longest;

    return difference < -tolerance;
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