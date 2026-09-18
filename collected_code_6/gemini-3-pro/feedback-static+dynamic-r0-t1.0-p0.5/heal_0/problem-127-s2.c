#include <stdio.h>
#include <stdlib.h>

long long multiply(int a, int b) {
    long long result = 0;
    long long abs_a = a;
    long long abs_b = b;
    int is_negative = 0;

    if ((abs_a < 0 && abs_b > 0) || (abs_a > 0 && abs_b < 0)) {
        is_negative = 1;
    }

    if (abs_a < 0) {
        abs_a = -abs_a;
    }
    if (abs_b < 0) {
        abs_b = -abs_b;
    }

    while (abs_b > 0) {
        if (abs_b & 1) {
            result += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }

    if (is_negative) {
        result = -result;
    }

    return result;
}

int main(void) {
    int a = 25;
    int b = -14;
    long long result = multiply(a, b);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}