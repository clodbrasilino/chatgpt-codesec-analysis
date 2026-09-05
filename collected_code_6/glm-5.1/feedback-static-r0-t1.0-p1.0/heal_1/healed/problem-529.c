#include <stdio.h>
#include <stdlib.h>

unsigned long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0 || n == 1) {
        return 2;
    }
    unsigned long long a = 2;
    unsigned long long b = 2;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = b + (a * 2);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return EXIT_FAILURE;
    }
    unsigned long long result = jacobsthal_lucas(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}