#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

typedef enum {
    EXTRACT_SUCCESS = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_SIZE_OVERFLOW,
    EXTRACT_ALLOCATION_FAILURE
} ExtractStatus;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static ExtractStatus extract_single_elements(
    const Tuple *tuples,
    size_t tuple_count,
    int **result,
    size_t *result_count)
{
    int *sorted_elements = NULL;
    int *single_elements = NULL;
    size_t total_elements = 0;
    size_t single_count = 0;
    size_t position = 0;

    if (result == NULL || result_count == NULL ||
        (tuple_count != 0 && tuples == NULL)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].length != 0 && tuples[i].elements == NULL) {
            return EXTRACT_INVALID_ARGUMENT;
        }

        if (tuples[i].length > SIZE_MAX - total_elements) {
            return EXTRACT_SIZE_OVERFLOW;
        }

        total_elements += tuples[i].length;
    }

    if (total_elements == 0) {
        return EXTRACT_SUCCESS;
    }

    if (total_elements > SIZE_MAX / sizeof(*sorted_elements)) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    sorted_elements = malloc(total_elements * sizeof(*sorted_elements));
    if (sorted_elements == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        for (size_t j = 0; j < tuples[i].length; ++j) {
            sorted_elements[position++] = tuples[i].elements[j];
        }
    }

    qsort(sorted_elements, total_elements, sizeof(*sorted_elements), compare_ints);

    for (size_t i = 0; i < total_elements;) {
        size_t end = i + 1;

        while (end < total_elements &&
               sorted_elements[end] == sorted_elements[i]) {
            ++end;
        }

        if (end - i == 1) {
            sorted_elements[single_count++] = sorted_elements[i];
        }

        i = end;
    }

    if (single_count == 0) {
        free(sorted_elements);
        return EXTRACT_SUCCESS;
    }

    single_elements = malloc(single_count * sizeof(*single_elements));
    if (single_elements == NULL) {
        free(sorted_elements);
        return EXTRACT_ALLOCATION_FAILURE;
    }

    position = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (bsearch(&tuples[i].elements[j],
                        sorted_elements,
                        single_count,
                        sizeof(*sorted_elements),
                        compare_ints) != NULL) {
                single_elements[position++] = tuples[i].elements[j];
            }
        }
    }

    free(sorted_elements);
    *result = single_elements;
    *result_count = single_count;

    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {2, 4};
    const int third[] = {3, 5, 6};
    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    int *single_elements = NULL;
    size_t single_count = 0;
    ExtractStatus status;

    status = extract_single_elements(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        &single_elements,
        &single_count);

    if (status != EXTRACT_SUCCESS) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < single_count; ++i) {
        if (printf("%d%s",
                   single_elements[i],
                   i + 1 < single_count ? " " : "\n") < 0) {
            free(single_elements);
            return EXIT_FAILURE;
        }
    }

    free(single_elements);
    return EXIT_SUCCESS;
}