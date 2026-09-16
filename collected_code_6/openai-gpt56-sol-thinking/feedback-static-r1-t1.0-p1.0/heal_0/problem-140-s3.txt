#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

typedef enum {
    EXTRACT_OK,
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
    size_t total_elements = 0;
    size_t single_count = 0;
    size_t position = 0;
    int *all_elements = NULL;
    int *single_elements = NULL;

    if (result == NULL || result_count == NULL ||
        (tuples == NULL && tuple_count != 0)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL && tuples[i].length != 0) {
            return EXTRACT_INVALID_ARGUMENT;
        }

        if (tuples[i].length > SIZE_MAX - total_elements) {
            return EXTRACT_SIZE_OVERFLOW;
        }

        total_elements += tuples[i].length;
    }

    if (total_elements == 0) {
        return EXTRACT_OK;
    }

    if (total_elements > SIZE_MAX / sizeof(*all_elements)) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    all_elements = malloc(total_elements * sizeof(*all_elements));
    if (all_elements == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        for (size_t j = 0; j < tuples[i].length; ++j) {
            all_elements[position++] = tuples[i].elements[j];
        }
    }

    qsort(all_elements, total_elements, sizeof(*all_elements), compare_ints);

    for (size_t i = 0; i < total_elements;) {
        size_t next = i + 1;

        while (next < total_elements &&
               all_elements[next] == all_elements[i]) {
            ++next;
        }

        if (next - i == 1) {
            ++single_count;
        }

        i = next;
    }

    if (single_count == 0) {
        free(all_elements);
        return EXTRACT_OK;
    }

    single_elements = malloc(single_count * sizeof(*single_elements));
    if (single_elements == NULL) {
        free(all_elements);
        return EXTRACT_ALLOCATION_FAILURE;
    }

    position = 0;

    for (size_t i = 0; i < total_elements;) {
        size_t next = i + 1;

        while (next < total_elements &&
               all_elements[next] == all_elements[i]) {
            ++next;
        }

        if (next - i == 1) {
            single_elements[position++] = all_elements[i];
        }

        i = next;
    }

    free(all_elements);
    *result = single_elements;
    *result_count = single_count;

    return EXTRACT_OK;
}

static int print_elements(const int *elements, size_t count)
{
    if (putchar('[') == EOF) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (printf("%d", elements[i]) < 0) {
            return 0;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {3, 4, 7};
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
        &single_count
    );

    if (status != EXTRACT_OK) {
        if (fputs("Failed to extract single elements.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!print_elements(single_elements, single_count)) {
        free(single_elements);
        return EXIT_FAILURE;
    }

    free(single_elements);
    return EXIT_SUCCESS;
}