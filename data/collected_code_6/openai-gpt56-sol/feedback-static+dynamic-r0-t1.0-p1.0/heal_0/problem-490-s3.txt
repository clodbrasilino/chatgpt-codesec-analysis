#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int is_symmetric(Pair a, Pair b)
{
    return a.first == b.second && a.second == b.first;
}

static Pair *extract_symmetric_pairs(const Pair *pairs, size_t count, size_t *result_count)
{
    Pair *result = NULL;
    size_t capacity = 0;

    if (result_count == NULL || (count > 0 && pairs == NULL)) {
        return NULL;
    }

    *result_count = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (is_symmetric(pairs[i], pairs[j])) {
                if (*result_count == capacity) {
                    size_t new_capacity = capacity == 0 ? 4 : capacity * 2;

                    if (new_capacity < capacity ||
                        new_capacity > SIZE_MAX / sizeof(*result)) {
                        free(result);
                        *result_count = 0;
                        return NULL;
                    }

                    Pair *new_result = realloc(
                        result, new_capacity * sizeof(*result)
                    );

                    if (new_result == NULL) {
                        free(result);
                        *result_count = 0;
                        return NULL;
                    }

                    result = new_result;
                    capacity = new_capacity;
                }

                result[*result_count] = pairs[i];
                ++(*result_count);
                break;
            }
        }
    }

    return result;
}

int main(void)
{
    Pair pairs[] = {
        {1, 2},
        {3, 4},
        {5, 9},
        {4, 3},
        {9, 5},
        {8, 7}
    };
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    size_t symmetric_count = 0;
    Pair *symmetric_pairs =
        extract_symmetric_pairs(pairs, pair_count, &symmetric_count);

    if (symmetric_pairs == NULL && symmetric_count == 0) {
        for (size_t i = 0; i < pair_count; ++i) {
            for (size_t j = i + 1; j < pair_count; ++j) {
                if (is_symmetric(pairs[i], pairs[j])) {
                    return EXIT_FAILURE;
                }
            }
        }
    }

    for (size_t i = 0; i < symmetric_count; ++i) {
        if (printf("(%d, %d)\n",
                   symmetric_pairs[i].first,
                   symmetric_pairs[i].second) < 0) {
            free(symmetric_pairs);
            return EXIT_FAILURE;
        }
    }

    free(symmetric_pairs);
    return EXIT_SUCCESS;
}