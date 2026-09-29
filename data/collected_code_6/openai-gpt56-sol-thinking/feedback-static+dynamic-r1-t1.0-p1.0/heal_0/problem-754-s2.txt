#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t index;
    int value;
} CommonIndexElement;

typedef enum {
    FIND_SUCCESS,
    FIND_INVALID_ARGUMENT,
    FIND_ALLOCATION_FAILURE
} FindResult;

FindResult find_common_index_elements(
    const int *first,
    size_t first_length,
    const int *second,
    size_t second_length,
    const int *third,
    size_t third_length,
    CommonIndexElement **elements,
    size_t *element_count)
{
    CommonIndexElement *result;
    size_t limit;
    size_t count;
    size_t index;

    if (elements == NULL || element_count == NULL ||
        (first == NULL && first_length != 0U) ||
        (second == NULL && second_length != 0U) ||
        (third == NULL && third_length != 0U)) {
        return FIND_INVALID_ARGUMENT;
    }

    *elements = NULL;
    *element_count = 0U;

    limit = first_length;
    if (second_length < limit) {
        limit = second_length;
    }
    if (third_length < limit) {
        limit = third_length;
    }

    count = 0U;
    for (index = 0U; index < limit; ++index) {
        if (first[index] == second[index] &&
            first[index] == third[index]) {
            ++count;
        }
    }

    if (count == 0U) {
        return FIND_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return FIND_ALLOCATION_FAILURE;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    count = 0U;
    for (index = 0U; index < limit; ++index) {
        if (first[index] == second[index] &&
            first[index] == third[index]) {
            result[count].index = index;
            result[count].value = first[index];
            ++count;
        }
    }

    *elements = result;
    *element_count = count;

    return FIND_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5, 6};
    const int second[] = {1, 9, 3, 8, 5};
    const int third[] = {1, 2, 3, 7, 5, 6};
    CommonIndexElement *elements = NULL;
    size_t element_count = 0U;
    size_t index;
    FindResult result;

    result = find_common_index_elements(
        first,
        sizeof(first) / sizeof(first[0]),
        second,
        sizeof(second) / sizeof(second[0]),
        third,
        sizeof(third) / sizeof(third[0]),
        &elements,
        &element_count);

    if (result != FIND_SUCCESS) {
        if (result == FIND_INVALID_ARGUMENT) {
            (void)fprintf(stderr, "Invalid argument\n");
        } else {
            (void)fprintf(stderr, "Memory allocation failed\n");
        }
        return EXIT_FAILURE;
    }

    for (index = 0U; index < element_count; ++index) {
        if (printf("Index %zu: %d\n",
                   elements[index].index,
                   elements[index].value) < 0) {
            free(elements);
            return EXIT_FAILURE;
        }
    }

    free(elements);
    return EXIT_SUCCESS;
}