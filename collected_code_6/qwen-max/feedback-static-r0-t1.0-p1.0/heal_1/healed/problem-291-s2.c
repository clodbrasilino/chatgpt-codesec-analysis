#include <stdio.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    
    int same = 0, diff = k;
    
    for (int i = 2; i <= n; i++) {
        int sum = same + diff;
        same = diff;
        diff = (k - 1) * sum;
    }
    
    return same + diff;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}