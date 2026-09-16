#include <stdio.h>

long long cubeSumOdd(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long odd = 2LL * i - 1;
        sum += odd * odd * odd;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    printf("%lld\n", cubeSumOdd(n));
    return 0;
}