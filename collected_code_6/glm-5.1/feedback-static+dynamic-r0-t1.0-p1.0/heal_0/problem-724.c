#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digit_power_sum(long long base, long long exponent) {
    if (base < 0 || exponent < 0) {
        return -1;
    }

    if (exponent == 0) {
        return 1;
    }

    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            if (base != 0 && result > LLONG_MAX / base) {
                return -1;
            }
            result *= base;
        }
        exponent /= 2;
        if (exponent > 0) {
            if (base > LLONG_MAX / base) {
                return -1;
            }
            base *= base;
        }
    }

    int sum = 0;
    while (result > 0) {
        sum += result % 10;
        result /= 10;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long long base = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || base < 0) {
        fprintf(stderr, "Invalid base\n");
        return 1;
    }

    long long exponent = strtoll(argv[2], &endptr, 10);
    if (*endptr != '\0' || exponent < 0) {
        fprintf(stderr, "Invalid exponent\n");
        return 1;
    }

    int sum = digit_power_sum(base, exponent);
    if (sum == -1) {
        fprintf(stderr, "Overflow or invalid input detected\n");
        return 1;
    }

    printf("%d\n", sum);
    return 0;
}