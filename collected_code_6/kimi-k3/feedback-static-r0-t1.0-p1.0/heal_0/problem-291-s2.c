#include <stdio.h>
#include <stdlib.h>

unsigned long long countWays(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    if (n == 1) {
        return (unsigned long long)k;
    }
    unsigned long long same = (unsigned long long)k;
    unsigned long long diff = (unsigned long long)k * (unsigned long long)(k - 1);
    unsigned long long total = same + diff;
    for (int i = 3; i <= n; i++) {
        same = diff;
        diff = total * (unsigned long long)(k - 1);
        total = same + diff;
    }
    return total;
}

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", countWays(n, k));
    return EXIT_SUCCESS;
}