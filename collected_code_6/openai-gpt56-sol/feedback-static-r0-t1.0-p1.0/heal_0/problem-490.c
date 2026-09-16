#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int find_symmetric_pairs(const Pair *pairs, size_t count,
                                Pair **result, size_t *result_count)
{
    Pair *output;
    size_t found = 0;

    if (pairs == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = malloc(count * sizeof(*output));
    if (output == NULL && count != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (pairs[i].first == pairs[j].second &&
                pairs[i].second == pairs[j].first) {
                output[found++] = pairs[i];
                output[found++] = pairs[j];
                break;
            }
        }
    }

    if (found == 0) {
        free(output);
        return 0;
    }

    Pair *resized = realloc(output, found * sizeof(*output));
    if (resized != NULL) {
        output = resized;
    }

    *result = output;
    *result_count = found;
    return 0;
}

int main(void)
{
    const Pair pairs[] = {
        {1, 2},
        {3, 4},
        {5, 9},
        {4, 3},
        {9, 5},
        {7, 8}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);
    Pair *symmetric_pairs = NULL;
    size_t symmetric_count = 0;

    if (find_symmetric_pairs(pairs, count, &symmetric_pairs,
                             &symmetric_count) != 0) {
        fputs("Failed to extract symmetric pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i + 1 < symmetric_count; i += 2) {
        printf("(%d, %d) and (%d, %d)\n",
               symmetric_pairs[i].first,
               symmetric_pairs[i].second,
               symmetric_pairs[i + 1].first,
               symmetric_pairs[i + 1].second);
    }

    free(symmetric_pairs);
    return EXIT_SUCCESS;
}