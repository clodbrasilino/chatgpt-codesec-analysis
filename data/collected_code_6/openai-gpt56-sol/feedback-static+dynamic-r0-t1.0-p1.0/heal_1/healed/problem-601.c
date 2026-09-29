#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *left, const void *right)
{
    const Pair *a = left;
    const Pair *b = right;

    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }

    return 0;
}

static int find_longest_chain(Pair *pairs, size_t count, Pair *chain)
{
    size_t chain_length = 0U;
    int last_end = 0;
    int has_last = 0;

    if (pairs == NULL || chain == NULL || count == 0U) {
        return 0;
    }

    qsort(pairs, count, sizeof(*pairs), compare_pairs);

    for (size_t i = 0U; i < count; ++i) {
        if (!has_last || pairs[i].first > last_end) {
            chain[chain_length++] = pairs[i];
            last_end = pairs[i].second;
            has_last = 1;
        }
    }

    if (chain_length > (size_t)INT_MAX) {
        return -1;
    }

    return (int)chain_length;
}

int main(void)
{
    Pair pairs[] = {
        {5, 24},
        {39, 60},
        {15, 28},
        {27, 40},
        {50, 90}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);
    Pair *chain;
    int chain_length;

    if (count > SIZE_MAX / sizeof(*chain)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    chain = malloc(count * sizeof(*chain));
    if (chain == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    chain_length = find_longest_chain(pairs, count, chain);
    if (chain_length < 0) {
        fputs("Chain length exceeds supported range.\n", stderr);
        free(chain);
        return EXIT_FAILURE;
    }

    printf("Longest chain length: %d\n", chain_length);

    for (int i = 0; i < chain_length; ++i) {
        printf(
            "(%d, %d)%s",
            chain[i].first,
            chain[i].second,
            i + 1 == chain_length ? "\n" : " "
        );
    }

    free(chain);
    return EXIT_SUCCESS;
}