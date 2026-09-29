#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long power(int a, int b) {
    if (a == 0 && b <= 0) {
        return 0;
    }
    long long result = 1;
    long long base = a;
    int exp = b;
    if (exp < 0) {
        base = 1 / base;
        exp = -exp;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return 1;
    }
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return 1;
    }
    int a = (int)val1;

    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return 1;
    }
    int b = (int)val2;

    long long res = power(a, b);
    printf("%lld\n", res);
    return 0;
}