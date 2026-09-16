#include <stdio.h>
#include <limits.h>

int multiply(int a, int b) {
    long long result = 0;
    long long abs_a = a;
    long long abs_b = b;
    int negative = 0;

    if (a < 0) {
        negative = !negative;
        abs_a = -abs_a;
    }
    if (b < 0) {
        negative = !negative;
        abs_b = -abs_b;
    }

    while (abs_b > 0) {
        if (abs_b & 1) {
            result += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }

    if (negative) {
        result = -result;
    }

    if (result > INT_MAX) {
        return INT_MAX;
    }
    if (result < INT_MIN) {
        return INT_MIN;
    }

    return (int)result;
}

int main(void) {
    printf("%d\n", multiply(5, 7));
    printf("%d\n", multiply(-5, 7));
    printf("%d\n", multiply(5, -7));
    printf("%d\n", multiply(-5, -7));
    printf("%d\n", multiply(INT_MIN, -1));
    printf("%d\n", multiply(INT_MAX, 2));
    return 0;
}