#include <stdio.h>
#include <math.h>

int count_quadratic_solutions(double a, double b, double c) {
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return -1;
    }

    if (a == 0.0) {
        if (b == 0.0) {
            if (c == 0.0) {
                return -1;
            }
            return 0;
        }
        return 1;
    }

    double discriminant = (b * b) - (4.0 * a * c);

    if (!isfinite(discriminant)) {
        return -1;
    }

    if (discriminant > 0.0) {
        return 2;
    } else if (discriminant == 0.0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    double a, b, c;
    /* Possible weaknesses found:
     *  Variable 'epsilon' is assigned a value that is never used. [unreadVariable]
     */
    double epsilon = 1e-9;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    int solutions = count_quadratic_solutions(a, b, c);

    if (solutions == -1) {
        return 1;
    }

    printf("%d\n", solutions);

    return 0;
}