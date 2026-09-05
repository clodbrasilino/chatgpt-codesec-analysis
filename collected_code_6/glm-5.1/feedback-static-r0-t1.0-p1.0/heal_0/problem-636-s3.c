#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool are_roots_reciprocal(double a, double b, double c) {
    if (a == 0.0) {
        return false;
    }

    if (a > 0.0) {
        if (c < a * (-1e-9)) {
            return false;
        }
    } else {
        if (c > a * 1e-9) {
            return false;
        }
    }

    double diff = a - c;
    if (fabs(diff) < 1e-9) {
        return true;
    }

    double magnitude = fmax(fabs(a), fabs(c));
    if (fabs(diff) / magnitude < 1e-9) {
        return true;
    }

    return false;
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