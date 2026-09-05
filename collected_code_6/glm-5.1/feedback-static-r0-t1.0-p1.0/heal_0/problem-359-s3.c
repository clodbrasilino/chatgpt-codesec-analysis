#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool is_one_root_twice_other(double a, double b, double c) {
    if (a == 0.0) {
        return false;
    }

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return false;
    }

    double sum_of_roots = -b / a;
    double product_of_roots = c / a;

    double condition1 = product_of_roots * 2.0 - sum_of_roots;
    double condition2 = product_of_roots / 2.0 - sum_of_roots;

    double epsilon = 1e-9;

    if (fabs(condition1) < epsilon || fabs(condition2) < epsilon) {
        return true;
    }

    return false;
}

int main() {
    double a, b, c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    if (is_one_root_twice_other(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}