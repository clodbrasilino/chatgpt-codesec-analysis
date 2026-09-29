#include <stdio.h>
#include <stdlib.h>

unsigned long long find_ln_lobb(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long lobb = 1;
    unsigned int i;

    for (i = 1; i <= n; i++) {
        lobb = lobb * (n + i) / i;
    }

    lobb = lobb * 2 / (n + 1);

    return lobb;
}

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        return 1;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    unsigned long long res = find_ln_lobb(n);

    printf("%llu\n", res);

    return 0;
}