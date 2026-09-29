#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int frequency_count(const IntList *lists, size_t list_count,
                           Frequency **result, size_t *result_count)
{
    size_t total = 0;
    size_t position = 0;
    size_t unique_count = 0;
    int *values = NULL;
    Frequency *frequencies = NULL;

    if (result == NULL || result_count == NULL ||
        (list_count > 0 && lists == NULL)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].values == NULL) {
            return -1;
        }
        if (lists[i].length > SIZE_MAX - total) {
            return -1;
        }
        total += lists[i].length;
    }

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = malloc(total * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (size_t i = 0; i < list_count; ++i) {
        for (size_t j = 0; j < lists[i].length; ++j) {
            values[position++] = lists[i].values[j];
        }
    }

    qsort(values, total, sizeof(*values), compare_ints);

    unique_count = 1;
    for (size_t i = 1; i < total; ++i) {
        if (values[i] != values[i - 1]) {
            ++unique_count;
        }
    }

    if (unique_count > SIZE_MAX / sizeof(*frequencies)) {
        free(values);
        return -1;
    }

    frequencies = malloc(unique_count * sizeof(*frequencies));
    if (frequencies == NULL) {
        free(values);
        return -1;
    }

    position = 0;
    frequencies[0].value = values[0];
    frequencies[0].count = 1;

    for (size_t i = 1; i < total; ++i) {
        if (values[i] == frequencies[position].value) {
            ++frequencies[position].count;
        } else {
            ++position;
            frequencies[position].value = values[i];
            frequencies[position].count = 1;
        }
    }

    free(values);
    *result = frequencies;
    *result_count = unique_count;
    return 0;
}

int main(void)
{
    int first[] = {1, 2, 2, 3};
    int second[] = {2, 3, 4};
    int third[] = {1, 4, 4, 5};
    IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    Frequency *frequencies = NULL;
    size_t frequency_count_value = 0;

    if (frequency_count(lists, sizeof(lists) / sizeof(lists[0]),
                        &frequencies, &frequency_count_value) != 0) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < frequency_count_value; ++i) {
        if (printf("%d: %zu\n", frequencies[i].value,
                   frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}