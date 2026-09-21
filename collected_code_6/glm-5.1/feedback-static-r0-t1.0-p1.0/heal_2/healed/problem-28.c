#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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
        if (res > ULLONG_MAX / (n - k + i)) {
            return 0;
        }
        res *= (n - k + i);
        res /= i;
    }
    return res;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (endptr1 == argv[1] || *endptr1 != '\0' || val1 < 0 || val1 > INT_MAX || errno == ERANGE) {
        return 1;
    }
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (endptr2 == argv[2] || *endptr2 != '\0' || val2 < 0 || val2 > INT_MAX || errno == ERANGE) {
        return 1;
    }
    int n = (int)val1;
    int k = (int)val2;
    unsigned long long result = binomial_coefficient(n, k);
    printf("%llu\n", result);
    return 0;
}