#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return k;
    }
    
    if (k == 1) {
        return (n <= 2) ? 1 : 0;
    }
    
    long long same = k;
    long long diff = (long long)k * (k - 1);
    
    for (int i = 3; i <= n; i++) {
        long long newSame = diff;
        long long newDiff = (same + diff) * (k - 1);
        same = newSame;
        diff = newDiff;
    }
    
    return same + diff;
}

int main(void) {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = countWays(n, k);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}