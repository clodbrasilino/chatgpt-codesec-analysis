#include <stdio.h>
#include <stdlib.h>

long long int countWays(int n, int k) {
    long long int total = k;
    int mod = 1000000007;

    /* Possible weaknesses found:
     *  The scope of the variable 'same' can be reduced. [variableScope]
     *  Variable 'same' is assigned a value that is never used. [unreadVariable]
     */
    long long int same = 0, diff = k;

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }

    for (int i = 2; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        diff = diff % mod;
        total = (same + diff) % mod;
    }

    return total;
}

int main() {
    int n, k;

    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }

    if (n < 0 || k < 0) {
        return 1;
    }

    long long int ways = countWays(n, k);
    printf("%lld\n", ways);

    return 0;
}