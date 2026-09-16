#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int checked_multiply(int a, int b, long long *result) {
    if (a != 0 && b > LLONG_MAX / a) {
        return 0;
    }
    *result = (long long)a * b;
    return 1;
}

static int checked_add(long long a, long long b, long long *result) {
    if (b > 0 && a > LLONG_MAX - b) {
        return 0;
    }
    if (b < 0 && a < LLONG_MIN - b) {
        return 0;
    }
    *result = a + b;
    return 1;
}

static int checked_pow4(int base, long long *result) {
    long long square;
    long long fourth;
    if (!checked_multiply(base, base, &square)) {
        return 0;
    }
    if (!checked_multiply(square, square, &fourth)) {
        return 0;
    }
    *result = fourth;
    return 1;
}

long long sum_fourth_power_odd(int n) {
    if (n < 0) {
        errno = EINVAL;
        return -1;
    }

    long long total = 0;
    int odd_number = 1;

    for (int i = 0; i < n; i++) {
        long long term;
        if (!checked_pow4(odd_number, &term)) {
            errno = ERANGE;
            return -1;
        }
        if (!checked_add(total, term, &total)) {
            errno = ERANGE;
            return -1;
        }
        if (odd_number > INT_MAX - 2) {
            errno = ERANGE;
            return -1;
        }
        odd_number += 2;
    }

    return total;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long long result = sum_fourth_power_odd(n);
    if (errno != 0) {
        perror("Error computing sum");
        return EXIT_FAILURE;
    }

    printf("Sum of fourth powers of first %d odd natural numbers: %lld\n", n, result);
    return EXIT_SUCCESS;
}