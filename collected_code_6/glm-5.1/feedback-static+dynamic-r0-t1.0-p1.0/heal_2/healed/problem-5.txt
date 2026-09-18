#include <stdio.h>
#include <stdlib.h>

long long count_dominoes(int n) {
    if (n < 0 || n % 2 != 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 2) {
        return 3;
    }
    long long a = 1;
    long long b = 3;
    for (int i = 4; i <= n; i += 2) {
        if (b > 2305843009213693951LL) {
            exit(EXIT_FAILURE);
        }
        long long c = 4 * b - a;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    long long result = count_dominoes(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}