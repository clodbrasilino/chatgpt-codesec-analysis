#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b);

int multiply(int a, int b) {
    long long abs_a = a;
    long long abs_b = b;
    long long result = 0;
    int is_negative = 0;

    if (abs_a < 0) {
        abs_a = -abs_a;
        is_negative ^= 1;
    }
    
    if (abs_b < 0) {
        abs_b = -abs_b;
        is_negative ^= 1;
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

    return (int)result;
}

int main(void) {
    int num1 = 15;
    int num2 = -4;
    int result = 0;

    result = multiply(num1, num2);
    
    printf("%d\n", result);

    return EXIT_SUCCESS;
}