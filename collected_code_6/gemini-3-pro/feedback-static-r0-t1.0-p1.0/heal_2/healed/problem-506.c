#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
    }
    
    return result;
}

int main(int argc, const char *const argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long n_long, k_long;

    errno = 0;
    n_long = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || argv[1] == endptr || n_long < 0 || n_long > INT_MAX) {
        printf("Invalid input parameters.\n");
        return 1;
    }

    errno = 0;
    k_long = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || argv[2] == endptr || k_long < 0 || k_long > INT_MAX) {
        printf("Invalid input parameters.\n");
        return 1;
    }

    int n = (int)n_long;
    int k = (int)k_long;

    if (n < 0 || k < 0 || k > n) {
        printf("Invalid input parameters.\n");
    } else {
        unsigned long long p = permutation(n, k);
        printf("P(%d, %d) = %llu\n", n, k, p);
    }
    
    return 0;
}