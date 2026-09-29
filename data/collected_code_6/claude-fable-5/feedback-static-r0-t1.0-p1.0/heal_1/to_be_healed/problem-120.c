#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int max_product_from_pairs(const Pair *pairs, size_t count, long long *result)
{
    size_t i;
    long long max;
    /* Possible weaknesses found:
     *  The scope of the variable 'product' can be reduced. [variableScope]
     */
    long long product;

    if (pairs == NULL || result == NULL || count == 0U) {
        return -1;
    }

    max = (long long)pairs[0].first * (long long)pairs[0].second;

    for (i = 1U; i < count; i++) {
        product = (long long)pairs[i].first * (long long)pairs[i].second;
        if (product > max) {
            max = product;
        }
    }

    *result = max;
    return 0;
}

int main(void)
{
    Pair pairs[] = {
        {2, 7},
        {2, 6},
        {1, 8},
        {4, 9}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    long long result = 0LL;
    int status;

    status = max_product_from_pairs(pairs, count, &result);
    if (status != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Maximum product: %lld\n", result);
    return EXIT_SUCCESS;
}