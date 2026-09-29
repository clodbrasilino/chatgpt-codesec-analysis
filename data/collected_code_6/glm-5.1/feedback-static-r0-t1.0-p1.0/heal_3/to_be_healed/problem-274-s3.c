#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_even_index_binomial_coefficients(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        long long val = 1LL << (n - 1);
        long long c = 1;
        int i;
        for (i = 0; i < n / 2; i++) {
            c = c * (n - i) / (i + 1);
        }
        return val + c;
    } else {
        return 1LL << (n - 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        return 1;
    }
    int n = (int)val;
    long long result = sum_even_index_binomial_coefficients(n);
    printf("%lld\n", result);
    return 0;
}