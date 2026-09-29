#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long checked_add(long long a, long long b, int *overflow) {
    if (a > 0 && b > 0 && a > LLONG_MAX - b) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b < 0 && a < LLONG_MIN - b) {
        *overflow = 1;
        return 0;
    }
    return a + b;
}

static long long checked_mul(long long a, long long b, int *overflow) {
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    return a * b;
}

long long demlo_number(int n) {
    if (n <= 0) {
        return 0;
    }

    int overflow = 0;
    long long result = 0;
    long long term = 0;

    for (int i = 1; i <= n; i++) {
        long long new_term = checked_mul(term, 10, &overflow);
        if (overflow) {
            return -1;
        }
        new_term = checked_add(new_term, 1, &overflow);
        if (overflow) {
            return -1;
        }
        term = new_term;
        result = checked_add(result, term, &overflow);
        if (overflow) {
            return -1;
        }
    }

    long long final_result = checked_mul(result, result, &overflow);
    if (overflow) {
        return -1;
    }
    return final_result;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (num < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    long long output = demlo_number(num);
    if (output == -1 && num > 0) {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", output);
    return EXIT_SUCCESS;
}