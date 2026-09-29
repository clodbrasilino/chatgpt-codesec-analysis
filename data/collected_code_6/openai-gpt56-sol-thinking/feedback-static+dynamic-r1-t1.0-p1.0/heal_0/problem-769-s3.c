#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    LIST_SUCCESS = 0,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE
} ListStatus;

ListStatus list_difference(
    const int *first,
    size_t first_count,
    const int *second,
    size_t second_count,
    int **difference,
    size_t *difference_count)
{
    int *result;
    size_t result_count = 0;

    if (difference == NULL || difference_count == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *difference = NULL;
    *difference_count = 0;

    if ((first_count > 0 && first == NULL) ||
        (second_count > 0 && second == NULL) ||
        first_count > SIZE_MAX / sizeof(*result)) {
        return LIST_INVALID_ARGUMENT;
    }

    if (first_count == 0) {
        return LIST_SUCCESS;
    }

    result = malloc(first_count * sizeof(*result));
    if (result == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < first_count; ++i) {
        int found = 0;

        for (size_t j = 0; j < second_count; ++j) {
            if (first[i] == second[j]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result[result_count++] = first[i];
        }
    }

    if (result_count == 0) {
        free(result);
        return LIST_SUCCESS;
    }

    *difference = result;
    *difference_count = result_count;
    return LIST_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 6};
    const int second[] = {2, 4, 6, 8};
    const size_t first_count = sizeof(first) / sizeof(first[0]);
    const size_t second_count = sizeof(second) / sizeof(second[0]);
    int *difference = NULL;
    size_t difference_count = 0;

    ListStatus status = list_difference(
        first,
        first_count,
        second,
        second_count,
        &difference,
        &difference_count);

    if (status != LIST_SUCCESS) {
        fputs("Unable to calculate the list difference.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < difference_count; ++i) {
        printf("%d%s", difference[i], i + 1 < difference_count ? " " : "\n");
    }

    free(difference);
    return EXIT_SUCCESS;
}