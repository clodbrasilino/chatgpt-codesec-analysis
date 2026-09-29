#include <stdio.h>
#include <stdlib.h>

unsigned long long perrin_sum(int n) {
    if (n < 0) return 0;
    if (n == 0) return 3;
    if (n == 1) return 3;
    if (n == 2) return 5;

    unsigned long long p0 = 3, p1 = 0, p2 = 2;
    unsigned long long sum = 5;

    for (int i = 3; i <= n; i++) {
        unsigned long long current = p0 + p1;
        sum += current;
        p0 = p1;
        p1 = p2;
        p2 = current;
    }

    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", perrin_sum(n));
    return EXIT_SUCCESS;
}