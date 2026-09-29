#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t cubeSumEvenNatural(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int64_t even = 2LL * i;
        if (even > 2097152) {
            return -1;
        }
        int64_t cube = even * even * even;
        if (sum > INT64_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0 || n > 1048576) {
        return 1;
    }
    printf("%" PRId64 "\n", cubeSumEvenNatural(n));
    return 0;
}