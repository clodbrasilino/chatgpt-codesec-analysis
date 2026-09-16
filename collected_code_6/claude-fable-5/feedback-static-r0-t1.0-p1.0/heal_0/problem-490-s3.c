#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

Pair *find_symmetric_pairs(const Pair *pairs, size_t count, size_t *result_count)
{
    Pair *result;
    size_t i;
    size_t j;
    size_t found;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if (pairs == NULL || count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(Pair));
    if (result == NULL) {
        return NULL;
    }

    found = 0;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (pairs[i].first == pairs[j].second &&
                pairs[i].second == pairs[j].first) {
                result[found].first = pairs[i].first;
                result[found].second = pairs[i].second;
                found++;
                break;
            }
        }
    }

    if (found == 0) {
        free(result);
        return NULL;
    }

    *result_count = found;
    return result;
}

int main(void)
{
    Pair input[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3},
        {7, 8}
    };
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t result_count = 0;
    Pair *result;
    size_t i;

    result = find_symmetric_pairs(input, input_count, &result_count);

    if (result == NULL) {
        if (printf("No symmetric pairs found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    for (i = 0; i < result_count; i++) {
        if (printf("(%d, %d)\n", result[i].first, result[i].second) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}