#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuples_equal(const Tuple *a, const Tuple *b)
{
    return a->first == b->first && a->second == b->second;
}

static int replace_duplicates(Tuple *tuples, size_t count, Tuple replacement)
{
    unsigned char *duplicate;

    if (count > 0 && tuples == NULL) {
        return -1;
    }

    if (count == 0) {
        return 0;
    }

    duplicate = calloc(count, sizeof(*duplicate));
    if (duplicate == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (tuples_equal(&tuples[i], &tuples[j])) {
                duplicate[i] = 1;
                duplicate[j] = 1;
            }
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (duplicate[i] != 0) {
            tuples[i] = replacement;
        }
    }

    free(duplicate);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {7, 8}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    const Tuple replacement = {-1, -1};

    if (replace_duplicates(tuples, count, replacement) != 0) {
        fputs("Failed to process tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}