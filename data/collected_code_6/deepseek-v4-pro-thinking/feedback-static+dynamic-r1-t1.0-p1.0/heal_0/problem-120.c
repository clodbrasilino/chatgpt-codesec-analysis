#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int max_product_from_tuples(const int tuples[][2], size_t count, long long *result) {
    if (tuples == NULL || count == 0 || result == NULL) {
        return -1;
    }

    long long max = LLONG_MIN;

    for (size_t i = 0; i < count; ++i) {
        long long product = (long long)tuples[i][0] * (long long)tuples[i][1];
        if (product > max) {
            max = product;
        }
    }

    *result = max;
    return 0;
}

int main(void) {
    int tuples[][2] = {
        { 2, 3 },
        { -1, 5 },
        { 4, -4 },
        { 0, 10 },
        { 7, 8 }
    };

    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long max = 0;

    if (max_product_from_tuples(tuples, count, &max) == 0) {
        printf("%lld\n", max);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}