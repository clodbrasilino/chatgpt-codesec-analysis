#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    if (k == 1) {
        if (n <= 2) return 1;
        return 0;
    }
    
    long long same = k;
    long long diff = k * (k - 1);
    
    for (int i = 3; i <= n; i++) {
        long long prev_diff = diff;
        diff = (same + diff) * (k - 1);
        same = prev_diff;
    }
    
    return same + diff;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    
    char *endptr_n;
    char *endptr_k;
    errno = 0;
    long val_n = strtol(argv[1], &endptr_n, 10);
    if (errno != 0 || endptr_n == argv[1] || val_n < 0 || val_n > INT_MAX) {
        fprintf(stderr, "Error: n must be a valid non-negative integer within range.\n");
        return 1;
    }
    
    errno = 0;
    long val_k = strtol(argv[2], &endptr_k, 10);
    if (errno != 0 || endptr_k == argv[2] || val_k < 0 || val_k > INT_MAX) {
        fprintf(stderr, "Error: k must be a valid non-negative integer within range.\n");
        return 1;
    }
    
    int n = (int)val_n;
    int k = (int)val_k;
    
    long long result = numWays(n, k);
    printf("%lld\n", result);
    
    return 0;
}