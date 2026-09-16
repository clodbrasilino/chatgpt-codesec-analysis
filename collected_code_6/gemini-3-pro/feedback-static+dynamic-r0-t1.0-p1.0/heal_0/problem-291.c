#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n == 0 || k == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }

    long long same = k;
    long long diff = (long long)k * (k - 1);
    long long total = same + diff;

    for (int i = 3; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        total = same + diff;
    }

    return total;
}

int main(void) {
    int n;
    int k;

    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n < 0 || k < 0) {
        fprintf(stderr, "Input must not be negative\n");
        return 1;
    }

    long long ways = countWays(n, k);
    printf("%lld\n", ways);

    return 0;
}