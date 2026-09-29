#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int extract_symmetric_pairs(const Pair *pairs, size_t count, Pair **result, size_t *result_count)
{
    Pair *symmetric;
    size_t capacity;
    size_t found = 0;

    if (result == NULL || result_count == NULL || (pairs == NULL && count != 0)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*symmetric)) {
        return -1;
    }

    capacity = count;
    symmetric = malloc(capacity * sizeof(*symmetric));
    if (symmetric == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        int has_reverse = 0;
        int already_added = 0;

        for (size_t j = 0; j < count; ++j) {
            if (i != j &&
                pairs[i].first == pairs[j].second &&
                pairs[i].second == pairs[j].first) {
                has_reverse = 1;
                break;
            }
        }

        if (!has_reverse) {
            continue;
        }

        for (size_t j = 0; j < found; ++j) {
            if ((symmetric[j].first == pairs[i].first &&
                 symmetric[j].second == pairs[i].second) ||
                (symmetric[j].first == pairs[i].second &&
                 symmetric[j].second == pairs[i].first)) {
                already_added = 1;
                break;
            }
        }

        if (!already_added) {
            symmetric[found++] = pairs[i];
        }
    }

    if (found == 0) {
        free(symmetric);
        return 0;
    }

    Pair *resized = realloc(symmetric, found * sizeof(*resized));
    if (resized != NULL) {
        symmetric = resized;
    }

    *result = symmetric;
    *result_count = found;
    return 0;
}

int main(void)
{
    Pair pairs[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3},
        {7, 8}
    };
    Pair *symmetric = NULL;
    size_t symmetric_count = 0;
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (extract_symmetric_pairs(
            pairs, pair_count, &symmetric, &symmetric_count) != 0) {
        fputs("Failed to extract symmetric pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < symmetric_count; ++i) {
        if (printf("(%d, %d) and (%d, %d)\n",
                   symmetric[i].first,
                   symmetric[i].second,
                   symmetric[i].second,
                   symmetric[i].first) < 0) {
            free(symmetric);
            return EXIT_FAILURE;
        }
    }

    free(symmetric);
    return EXIT_SUCCESS;
}