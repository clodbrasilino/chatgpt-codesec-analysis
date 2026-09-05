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

    if (fabs(9.0 * a * c - 2.0 * b * b) < 1e-9) {
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