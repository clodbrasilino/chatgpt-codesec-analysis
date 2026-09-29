#include <stdio.h>
#include <stdlib.h>

unsigned long long find_jacobsthal(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long c = 0;

    for (int i = 2; i <= n; i++) {
        c = b + 2 * a;
        a = b;
        b = c;
    }

    return c;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0 || n > 64) {
        return 1;
    }

    unsigned long long result = find_jacobsthal(n);
    printf("%llu\n", result);

    return 0;
}