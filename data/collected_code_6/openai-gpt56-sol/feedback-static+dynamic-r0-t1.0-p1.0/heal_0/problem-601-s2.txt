#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *lhs, const void *rhs)
{
    const Pair *a = lhs;
    const Pair *b = rhs;

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

static size_t longest_chain(Pair *pairs, size_t count)
{
    if (pairs == NULL || count == 0U) {
        return 0U;
    }

    qsort(pairs, count, sizeof(*pairs), compare_pairs);

    size_t chain_length = 1U;
    int last_end = pairs[0].second;

    for (size_t i = 1U; i < count; ++i) {
        if (pairs[i].first > last_end) {
            ++chain_length;
            last_end = pairs[i].second;
        }
    }

    return chain_length;
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
    const size_t result = longest_chain(pairs, count);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}