#include <stdio.h>

double power(double a, int b) {
    double result = 1.0;
    if (b == 0) return result;
    int abs_b = b > 0 ? b : -b;
    while (abs_b) {
        if (abs_b & 1) result *= a;
        a *= a;
        abs_b >>= 1;
    }
    return b > 0 ? result : 1 / result;
}

int main() {
    double base = 2.0;
    int exponent = -3;
    printf("%.2f\n", power(base, exponent));
    return 0;
}