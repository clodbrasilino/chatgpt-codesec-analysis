#include <stdio.h>
#include <stdlib.h>

long long countWays(int n) {
    if (n < 0 || n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }

    long long *f = (long long *)malloc((n + 1) * sizeof(long long));
    long long *g = (long long *)malloc((n + 1) * sizeof(long long));

    if (f == NULL || g == NULL) {
        free(f);
        free(g);
        return -1;
    }

    f[0] = 1;
    f[1] = 0;
    g[0] = 0;
    g[1] = 1;

    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 2] + 2 * g[i - 1];
        g[i] = f[i - 1] + g[i - 2];
    }

    long long result = f[n];

    free(f);
    free(g);

    return result;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    long long ways = countWays(n);

    if (ways == -1) {
        return 1;
    }

    printf("%lld\n", ways);

    return 0;
}