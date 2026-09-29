#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool are_roots_equal_opposite(double a, double b, double c) {
    if (a == 0.0) {
        return false;
    }
    if (b != 0.0) {
        return false;
    }
    if (c == 0.0) {
        return true;
    }
    long double discriminant = (long double)b * b - 4.0L * (long double)a * (long double)c;
    if (discriminant < 0.0L) {
        return false;
    }
    long double sqrt_discriminant = sqrtl(discriminant);
    long double root1 = (-(long double)b + sqrt_discriminant) / (2.0L * (long double)a);
    long double root2 = (-(long double)b - sqrt_discriminant) / (2.0L * (long double)a);
    return fabsl(root1 + root2) < 1e-12L;
}

int main() {
    double a, b, c;
    if (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        if (are_roots_equal_opposite(a, b, c)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}