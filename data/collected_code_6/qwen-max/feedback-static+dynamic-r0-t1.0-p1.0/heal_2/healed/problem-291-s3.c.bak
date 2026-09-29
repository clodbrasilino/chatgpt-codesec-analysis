#include <stdio.h>
#include <stdint.h>

int64_t numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int64_t same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int64_t temp = diff;
        diff = (k - 1) * (same + diff);
        same = (k - 1) * temp;
    }
    return same + diff;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%lld\n", numWays(n, k));
    return 0;
}