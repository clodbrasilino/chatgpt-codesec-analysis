#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int find_symmetric_pairs(const Pair *pairs, size_t count, Pair **result, size_t *result_count)
{
    size_t found;
    Pair *temp;

    if (pairs == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return 0;
    }

    temp = malloc(count * sizeof(Pair));
    if (temp == NULL) {
        return -1;
    }

    found = 0;
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            if (pairs[i].first == pairs[j].second &&
                pairs[i].second == pairs[j].first) {
                temp[found] = pairs[i];
                found++;
                break;
            }
        }
    }

    if (found == 0) {
        free(temp);
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    *result = realloc(temp, found * sizeof(Pair));
    if (*result == NULL) {
        *result = temp;
    }
    *result_count = found;
    return 0;
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
    Pair *symmetric = NULL;
    size_t symmetric_count = 0;

    if (find_symmetric_pairs(input, input_count, &symmetric, &symmetric_count) != 0) {
        fprintf(stderr, "Error: failed to find symmetric pairs\n");
        return EXIT_FAILURE;
    }

    if (symmetric_count == 0) {
        printf("No symmetric pairs found\n");
    } else {
        printf("Symmetric pairs:\n");
        for (size_t i = 0; i < symmetric_count; i++) {
            printf("(%d, %d)\n", symmetric[i].first, symmetric[i].second);
        }
    }

    free(symmetric);
    return EXIT_SUCCESS;
}