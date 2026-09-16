#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_perrin(int n) {
    if (n < 0) {
        return 0;
    }
    
    if (n == 0) return 3;
    if (n == 1) return 3;
    if (n == 2) return 5;

    unsigned long long p0 = 3;
    unsigned long long p1 = 0;
    unsigned long long p2 = 2;
    unsigned long long sum = p0 + p1 + p2;

    for (int i = 3; i <= n; i++) {
        unsigned long long p_next = p0 + p1;
        sum += p_next;
        p0 = p1;
        p1 = p2;
        p2 = p_next;
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

    unsigned long long result = sum_perrin(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}