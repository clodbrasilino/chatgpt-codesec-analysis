#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return false;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double largest = fmax(a, fmax(b, c));
    double sum = a + b + c;

    return isfinite(sum) && (sum - largest > largest);
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