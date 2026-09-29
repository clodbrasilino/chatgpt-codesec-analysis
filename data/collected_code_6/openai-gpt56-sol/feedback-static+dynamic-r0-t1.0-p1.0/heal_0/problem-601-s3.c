#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

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

static size_t longest_chain(Pair *pairs, size_t count, Pair *chain)
{
    size_t chain_length = 0;

    if (pairs == NULL || chain == NULL || count == 0) {
        return 0;
    }

    qsort(pairs, count, sizeof(*pairs), compare_pairs);

    chain[chain_length++] = pairs[0];

    for (size_t i = 1; i < count; ++i) {
        if (pairs[i].first > chain[chain_length - 1].second) {
            chain[chain_length++] = pairs[i];
        }
    }

    return chain_length;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid pair count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == 0) {
        puts("Longest chain length: 0");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(Pair)) {
        fputs("Pair count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    Pair *pairs = malloc(count * sizeof(*pairs));
    Pair *chain = malloc(count * sizeof(*chain));

    if (pairs == NULL || chain == NULL) {
        free(pairs);
        free(chain);
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d %d", &pairs[i].first, &pairs[i].second) != 2) {
            free(chain);
            free(pairs);
            fputs("Invalid pair input\n", stderr);
            return EXIT_FAILURE;
        }

        if (pairs[i].first >= pairs[i].second) {
            free(chain);
            free(pairs);
            fputs("Each pair must satisfy first < second\n", stderr);
            return EXIT_FAILURE;
        }
    }

    size_t chain_length = longest_chain(pairs, count, chain);

    printf("Longest chain length: %zu\n", chain_length);
    for (size_t i = 0; i < chain_length; ++i) {
        printf("(%d, %d)%c",
               chain[i].first,
               chain[i].second,
               i + 1 == chain_length ? '\n' : ' ');
    }

    free(chain);
    free(pairs);
    return EXIT_SUCCESS;
}