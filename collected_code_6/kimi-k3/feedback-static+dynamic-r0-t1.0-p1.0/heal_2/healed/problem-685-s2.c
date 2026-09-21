#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    if (num == 2) {
        return true;
    }
    if (num % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= num / i; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

long long sum_of_primes(int n) {
    if (n < 2) {
        return 0;
    }
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    long val;
    char *endptr;
    char buffer[64];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < 1) {
        return EXIT_FAILURE;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    n = (int)val;
    printf("%lld\n", sum_of_primes(n));

    return EXIT_SUCCESS;
}