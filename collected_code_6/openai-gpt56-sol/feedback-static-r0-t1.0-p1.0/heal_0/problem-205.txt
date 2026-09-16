#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    long long first;
    long long second;
} Tuple;

typedef struct {
    size_t left;
    size_t right;
} Inversion;

static int find_inversions(const Tuple *tuples, size_t count,
                           Inversion **inversions, size_t *inversion_count)
{
    size_t i;
    size_t j;
    size_t total = 0U;
    size_t index = 0U;
    Inversion *result = NULL;

    if (inversions == NULL || inversion_count == NULL ||
        (tuples == NULL && count != 0U)) {
        return -1;
    }

    *inversions = NULL;
    *inversion_count = 0U;

    for (i = 0U; i < count; ++i) {
        for (j = i + 1U; j < count; ++j) {
            if (tuples[i].first > tuples[j].first &&
                tuples[i].second > tuples[j].second) {
                if (total == SIZE_MAX) {
                    return -1;
                }
                ++total;
            }
        }
    }

    if (total == 0U) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(total * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        for (j = i + 1U; j < count; ++j) {
            if (tuples[i].first > tuples[j].first &&
                tuples[i].second > tuples[j].second) {
                result[index].left = i;
                result[index].right = j;
                ++index;
            }
        }
    }

    *inversions = result;
    *inversion_count = total;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {5, 8},
        {3, 6},
        {4, 7},
        {2, 1},
        {6, 9}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    Inversion *inversions = NULL;
    size_t inversion_count = 0U;
    size_t i;
    int status;

    status = find_inversions(tuples, tuple_count,
                             &inversions, &inversion_count);
    if (status != 0) {
        fputs("Failed to find inversions.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < inversion_count; ++i) {
        const size_t left = inversions[i].left;
        const size_t right = inversions[i].right;

        if (printf("(%lld, %lld) > (%lld, %lld)\n",
                   tuples[left].first, tuples[left].second,
                   tuples[right].first, tuples[right].second) < 0) {
            free(inversions);
            return EXIT_FAILURE;
        }
    }

    free(inversions);
    return EXIT_SUCCESS;
}