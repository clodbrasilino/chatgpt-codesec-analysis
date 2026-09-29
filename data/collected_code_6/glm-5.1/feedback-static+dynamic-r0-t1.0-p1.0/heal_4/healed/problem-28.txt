#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    if (k == 0 || k == n) {
        return 1;
    }

    if (k > n - k) {
        k = n - k;
    }

    unsigned long long res = 1;

    for (int i = 1; i <= k; i++) {
        if (res > (unsigned long long)(-1) / (n - k + i)) {
            return 0;
        }
        res *= (n - k + i);
        res /= i;
    }

    return res;
}

int str_to_int(const char *str, int *out) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < 0) {
        return -1;
    }
    if (endptr == str || *endptr != '\0') {
        return -1;
    }

    *out = (int)val;
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return 1;
    }

    int n, k;

    if (str_to_int(argv[1], &n) != 0 || str_to_int(argv[2], &k) != 0) {
        return 1;
    }

    unsigned long long result = binomial_coefficient(n, k);

    printf("%llu\n", result);

    return 0;
}