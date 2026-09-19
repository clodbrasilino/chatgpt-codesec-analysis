#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;

    long long same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        long long temp = diff;
        if ((k - 1) > INT_MAX / (same + diff) || (k - 1) * (same + diff) < 0 || (k - 1) * (same + diff) > LLONG_MAX) return -1;
        diff = (k - 1) * (same + diff);
        if ((k - 1) > INT_MAX / temp || (k - 1) * temp < 0 || (k - 1) * temp > LLONG_MAX) return -1;
        same = (k - 1) * temp;
    }
    if (same + diff < 0 || same + diff > INT_MAX) return -1;
    return same + diff;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    printf("%d\n", numWays(n, k));
    return 0;
}