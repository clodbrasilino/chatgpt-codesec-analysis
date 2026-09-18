#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }
    if (k == 0) {
        return 0;
    }

    unsigned long long same = k;
    unsigned long long diff = (unsigned long long)k * (k - 1);
    unsigned long long total = same + diff;

    for (int i = 3; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        total = same + diff;
    }

    return (long long)total;
}

int main(void) {
    int n = 0;
    int k = 0;

    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }

    if (n < 0 || k < 0) {
        return 1;
    }

    long long result = countWays(n, k);
    printf("%lld\n", result);

    return 0;
}