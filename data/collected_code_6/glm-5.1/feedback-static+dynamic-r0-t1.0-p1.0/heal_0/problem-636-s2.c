#include <stdio.h>
#include <math.h>
#include <float.h>

int are_roots_reciprocal(double a, double b, double c) {
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return 0;
    }
    if (fabs(c) < DBL_EPSILON) {
        return 0;
    }
    if (fabs(a - c) < DBL_EPSILON) {
        return 1;
    }
    return 0;
}

int main() {
    double a, b, c;
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    if (are_roots_reciprocal(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}