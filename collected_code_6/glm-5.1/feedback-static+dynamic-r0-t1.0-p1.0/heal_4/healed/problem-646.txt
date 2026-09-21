#include <stdio.h>
#include <stdlib.h>

long long count_cubes(long long n, long long k) {
    if (n <= 0 || k <= 0 || k > n) {
        return 0;
    }
    long long diff = n - k + 1;
    return diff * diff * diff;
}

int main(int argc, char * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr_n, *endptr_k;
    long long val_n = strtoll(argv[1], &endptr_n, 10);
    long long val_k = strtoll(argv[2], &endptr_k, 10);
    
    if (*endptr_n != '\0' || *endptr_k != '\0' || val_n <= 0 || val_k <= 0) {
        fprintf(stderr, "Error: n and k must be positive integers\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_cubes(val_n, val_k);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}