#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    LIST_SUCCESS = 0,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE,
    LIST_SIZE_OVERFLOW
} ListStatus;

static int list_contains(const int *list, size_t count, int value)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        if (list[i] == value) {
            return 1;
        }
    }

    return 0;
}

static ListStatus list_difference(
    const int *first,
    size_t first_count,
    const int *second,
    size_t second_count,
    int **result,
    size_t *result_count)
{
    int *difference;
    size_t count = 0;
    size_t i;

    if (result == NULL || result_count == NULL ||
        (first == NULL && first_count != 0) ||
        (second == NULL && second_count != 0)) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (first_count == 0) {
        return LIST_SUCCESS;
    }

    if (first_count > SIZE_MAX / sizeof(*difference)) {
        return LIST_SIZE_OVERFLOW;
    }

    difference = malloc(first_count * sizeof(*difference));
    if (difference == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    for (i = 0; i < first_count; ++i) {
        if (!list_contains(second, second_count, first[i])) {
            difference[count++] = first[i];
        }
    }

    if (count == 0) {
        free(difference);
        return LIST_SUCCESS;
    }

    *result = difference;
    *result_count = count;
    return LIST_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 6};
    const int second[] = {2, 4, 6, 8};
    int *difference = NULL;
    size_t difference_count = 0;
    size_t i;
    ListStatus status;

    status = list_difference(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        &difference,
        &difference_count
    );

    if (status != LIST_SUCCESS) {
        fprintf(stderr, "Failed to calculate list difference: %d\n", status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < difference_count; ++i) {
        printf("%d%s", difference[i], i + 1 == difference_count ? "\n" : " ");
    }

    free(difference);
    return EXIT_SUCCESS;
}