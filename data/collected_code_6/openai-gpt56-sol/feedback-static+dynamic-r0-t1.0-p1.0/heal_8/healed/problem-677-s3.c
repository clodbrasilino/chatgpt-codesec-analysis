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
    double x;
    double y;

    if (longest == a) {
        x = b;
        y = c;
    } else if (longest == b) {
        x = a;
        y = c;
    } else {
        x = a;
        y = b;
    }

    if (x > y) {
        double temporary = x;
        x = y;
        y = temporary;
    }

    return longest - y < x;
}

int main(void)
{
    double a;
    double b;
    double c;
    char extra;

    if (scanf(" %lf %lf %lf", &a, &b, &c) != 3 ||
        scanf(" %c", &extra) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%d\n", is_valid_triangle(a, b, c) ? 1 : 0);
    return 0;
}