#include <stdio.h>
#include <limits.h>

long long cube_sum_odd(int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        long long cube = odd * odd * odd;
        if (cube > LLONG_MAX - sum) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    printf("%lld\n", cube_sum_odd(n));
    return 0;
}