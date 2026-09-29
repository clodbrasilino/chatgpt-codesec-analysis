#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a non-negative integer within valid range.\n");
        return 1;
    }
    int n = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || endptr == argv[2] || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Error: k must be a non-negative integer within valid range.\n");
        return 1;
    }
    int k = (int)val;
    
    long long result = numWays(n, k);
    printf("%lld\n", result);
    
    return 0;
}