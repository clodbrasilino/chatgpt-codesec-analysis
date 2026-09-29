#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    unsigned long long result = 1;
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    for (int i = 0; i < k; i++) {
        if (result > ULLONG_MAX / (n - i)) {
            return 0;
        }
        result *= (n - i);
    }
    return result;
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }

    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno == ERANGE || *endptr1 != '\0' || endptr1 == argv[1] || val1 < 0 || val1 > INT_MAX) {
        fprintf(stderr, "Invalid input for n\n");
        return 1;
    }

    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno == ERANGE || *endptr2 != '\0' || endptr2 == argv[2] || val2 < 0 || val2 > INT_MAX) {
        fprintf(stderr, "Invalid input for k\n");
        return 1;
    }

    int n = (int)val1;
    int k = (int)val2;
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return 0;
}