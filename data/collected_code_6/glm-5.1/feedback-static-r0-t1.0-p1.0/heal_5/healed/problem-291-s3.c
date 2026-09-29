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
    long long total = same + diff;
    
    for (int i = 3; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        total = same + diff;
    }
    
    return total;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || val1 < 0 || val1 > INT_MAX) {
        return 1;
    }
    int n = (int)val1;

    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || val2 < 0 || val2 > INT_MAX) {
        return 1;
    }
    int k = (int)val2;
    
    long long result = numWays(n, k);
    printf("%lld\n", result);
    
    return 0;
}