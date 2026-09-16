#include <stdio.h>

int countWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int same = 0, diff = k, total = same + diff;
    for (int i = 2; i <= n; i++) {
        same = diff;
        diff = (k - 1) * total;
        total = same + diff;
    }
    return total;
}

int main() {
    int n = 3;
    int k = 2;
    printf("Total number of ways: %d\n", countWays(n, k));
    return 0;
}