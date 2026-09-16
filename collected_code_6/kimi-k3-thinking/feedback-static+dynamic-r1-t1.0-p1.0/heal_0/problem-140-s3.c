#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuples_equal(Tuple a, Tuple b)
{
    return a.first == b.first && a.second == b.second;
}

size_t extract_singly_occurring(const Tuple *tuples, size_t count, Tuple **result)
{
    size_t i;
    size_t j;
    size_t out_count;
    Tuple *out;
    int is_unique;

    if (result == NULL) {
        return 0;
    }
    *result = NULL;

    if (tuples == NULL || count == 0) {
        return 0;
    }

    out = malloc(count * sizeof(*out));
    if (out == NULL) {
        return 0;
    }

    out_count = 0;
    for (i = 0; i < count; ++i) {
        is_unique = 1;
        for (j = 0; j < count; ++j) {
            if (i != j && tuples_equal(tuples[i], tuples[j])) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            out[out_count] = tuples[i];
            ++out_count;
        }
    }

    if (out_count == 0) {
        free(out);
        return 0;
    }

    *result = out;
    return out_count;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 4},
        {5, 6},
        {3, 4},
        {7, 8},
        {5, 6},
        {9, 0}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Tuple *result = NULL;
    size_t result_count;
    size_t i;

    result_count = extract_singly_occurring(tuples, count, &result);

    printf("Elements occurring singly:\n");
    for (i = 0; i < result_count; ++i) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    free(result);

    return EXIT_SUCCESS;
}