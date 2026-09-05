#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        if (result > ULLONG_MAX / (n - i)) {
            exit(EXIT_FAILURE);
        }
        result *= (n - i);
    }
    return result;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val1;
    int k = (int)val2;
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}