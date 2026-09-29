#include <stdio.h>
#include <limits.h>

long long cubeSumEvenNatural(int n) {
    if (n < 0 || n > 2097151) {
        return 0;
    }
    long long sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        long long even = 2LL * i;
        sum += even * even * even;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    printf("%lld\n", cubeSumEvenNatural(n));
    return 0;
}