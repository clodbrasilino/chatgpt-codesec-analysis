#include <stdio.h>
#include <math.h>

int count_quadratic_solutions(double a, double b, double c, double epsilon) {
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return -1;
    }

    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
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

    if (discriminant > epsilon) {
        return 2;
    } else if (discriminant < -epsilon) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    double a, b, c;
    double epsilon = 1e-9;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    int solutions = count_quadratic_solutions(a, b, c, epsilon);

    if (solutions == -1) {
        return 1;
    }

    printf("%d\n", solutions);

    return 0;
}