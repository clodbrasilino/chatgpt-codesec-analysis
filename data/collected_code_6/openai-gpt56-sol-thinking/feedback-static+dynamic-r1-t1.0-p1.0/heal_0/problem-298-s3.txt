#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t count;
} IntList;

typedef struct {
    const IntList *lists;
    size_t count;
} NestedIntList;

typedef struct {
    int *elements;
    size_t count;
} IntListResult;

typedef enum {
    FIND_SUCCESS,
    FIND_INVALID_ARGUMENT,
    FIND_SIZE_ERROR,
    FIND_ALLOCATION_ERROR
} FindStatus;

static int contains(const IntList *list, int value)
{
    size_t i;

    for (i = 0; i < list->count; ++i) {
        if (list->elements[i] == value) {
            return 1;
        }
    }

    return 0;
}

FindStatus find_nested_elements_present(
    const NestedIntList *nested,
    const IntList *other,
    IntListResult *result)
{
    size_t i;
    size_t j;
    size_t match_count = 0;
    size_t output_index = 0;
    int *matches;

    if (result == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    result->elements = NULL;
    result->count = 0;

    if (nested == NULL || other == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    if ((nested->count != 0 && nested->lists == NULL) ||
        (other->count != 0 && other->elements == NULL)) {
        return FIND_INVALID_ARGUMENT;
    }

    for (i = 0; i < nested->count; ++i) {
        const IntList *current = &nested->lists[i];

        if (current->count != 0 && current->elements == NULL) {
            return FIND_INVALID_ARGUMENT;
        }

        for (j = 0; j < current->count; ++j) {
            if (contains(other, current->elements[j])) {
                if (match_count == SIZE_MAX) {
                    return FIND_SIZE_ERROR;
                }
                ++match_count;
            }
        }
    }

    if (match_count == 0) {
        return FIND_SUCCESS;
    }

    if (match_count > SIZE_MAX / sizeof(*matches)) {
        return FIND_SIZE_ERROR;
    }

    matches = malloc(match_count * sizeof(*matches));
    if (matches == NULL) {
        return FIND_ALLOCATION_ERROR;
    }

    for (i = 0; i < nested->count; ++i) {
        const IntList *current = &nested->lists[i];

        for (j = 0; j < current->count; ++j) {
            if (contains(other, current->elements[j])) {
                matches[output_index++] = current->elements[j];
            }
        }
    }

    result->elements = matches;
    result->count = match_count;

    return FIND_SUCCESS;
}

static int print_result(const IntListResult *result)
{
    size_t i;

    if (putchar('[') == EOF) {
        return 0;
    }

    for (i = 0; i < result->count; ++i) {
        if (i != 0 && printf(", ") < 0) {
            return 0;
        }

        if (printf("%d", result->elements[i]) < 0) {
            return 0;
        }
    }

    if (printf("]\n") < 0) {
        return 0;
    }

    return 1;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {2, 7, 8, 5};
    const IntList rows[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    const int comparison_values[] = {2, 5, 8, 10};
    const NestedIntList nested = {
        rows,
        sizeof(rows) / sizeof(rows[0])
    };
    const IntList comparison = {
        comparison_values,
        sizeof(comparison_values) / sizeof(comparison_values[0])
    };
    IntListResult result;
    FindStatus status;

    status = find_nested_elements_present(&nested, &comparison, &result);
    if (status != FIND_SUCCESS) {
        if (fprintf(stderr, "Unable to find matching elements.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!print_result(&result)) {
        free(result.elements);
        return EXIT_FAILURE;
    }

    free(result.elements);
    return EXIT_SUCCESS;
}