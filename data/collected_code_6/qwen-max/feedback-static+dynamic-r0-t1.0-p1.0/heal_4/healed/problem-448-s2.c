#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t perrin(uint64_t n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;

    uint64_t a = 3, b = 0, c = 2;
    for (uint64_t i = 3; i <= n; i++) {
        uint64_t d = a + b;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

uint64_t sum_of_perrin(uint64_t n) {
    uint64_t sum = 0;
    for (uint64_t i = 0; i <= n; i++) {
        sum += perrin(i);
    }
    return sum;
}

int main() {
    int64_t n;
    if (scanf("%ld", &n) != 1 || n < 0) {
        return EXIT_FAILURE;
    }

    uint64_t result = sum_of_perrin(n);
    printf("The sum of the first %" PRId64 " Perrin numbers is: %" PRIu64 "\n", n, result);

    return EXIT_SUCCESS;
}