#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
    long long high;
    unsigned long long low;
} bigint;

bigint add(bigint a, bigint b) {
    bigint result = {0, 0};
    unsigned long long carry_low = (a.low > UINT64_MAX - b.low);
    result.low = a.low + b.low;
    if (carry_low) result.high = 1;
    result.high += a.high + b.high + (result.low < a.low);
    if (result.low < a.low) {
        result.low = 1;
    }
    return result;
}

bigint lucas_number(int n) {
    if (n == 0) return (bigint){0, 2};
    if (n == 1) return (bigint){0, 1};

    bigint a = {0, 2}, b = {0, 1};
    for (int i = 2; i <= n; ++i) {
        bigint c = add(a, b);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the index of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Index must be non-negative\n");
        return EXIT_FAILURE;
    }

    bigint result = lucas_number(n);
    printf("The %dth Lucas number is: %" PRId64 "%020" PRIu64 "\n", n, (int64_t)result.high, (uint64_t)result.low);
    return EXIT_SUCCESS;
}