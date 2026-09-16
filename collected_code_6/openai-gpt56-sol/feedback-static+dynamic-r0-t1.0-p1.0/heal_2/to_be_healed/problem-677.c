#include <math.h>
#include <stdbool.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

static bool is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return false;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }

    double sides[3] = {a, b, c};

    if (sides[0] > sides[1]) {
        double temp = sides[0];
        sides[0] = sides[1];
        sides[1] = temp;
    }

    if (sides[1] > sides[2]) {
        double temp = sides[1];
        sides[1] = sides[2];
        sides[2] = temp;
    }

    if (sides[0] > sides[1]) {
        double temp = sides[0];
        sides[0] = sides[1];
        sides[1] = temp;
    }

    return sides[0] > sides[2] - sides[1];
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