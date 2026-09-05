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

    double num = 9.0 * a * c;
    double den = a * a;
    double diff = num - den;

    if (fabs(diff) < 1e-9 * fmax(fabs(num), fabs(den))) {
        return true;
    }

    return false;
}

int main() {
    double a, b, c;
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    
    bool result = is_one_root_twice_other(a, b, c);
    printf("%s\n", result ? "True" : "False");
    
    return 0;
}