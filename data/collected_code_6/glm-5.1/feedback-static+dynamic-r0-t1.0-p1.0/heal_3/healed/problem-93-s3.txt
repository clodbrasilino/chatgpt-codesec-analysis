#include <stdio.h>

long long power(int a, int b) {
    if (b == 0) {
        return 1;
    }

    long long abs_b = b;
    if (b < 0) {
        abs_b = -abs_b;
    }

    long long result = 1;
    long long base = a;

    while (abs_b > 0) {
        if (abs_b % 2 == 1) {
            result *= base;
        }
        base *= base;
        abs_b /= 2;
    }

    if (b < 0) {
        return 0;
    }

    return result;
}

int main(void) {
    printf("%lld\n", power(3, 4));
    printf("%lld\n", power(2, 3));
    printf("%lld\n", power(5, 5));
    return 0;
}