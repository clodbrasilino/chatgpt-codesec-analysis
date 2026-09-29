#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;
    return (a > b) - (a < b);
}

static bool frequency_count(const IntList *lists, size_t list_count,
                            Frequency **frequencies, size_t *frequency_count_out)
{
    size_t total = 0;
    size_t offset = 0;
    size_t unique_count = 0;
    int *values = NULL;
    Frequency *result = NULL;

    if (frequencies == NULL || frequency_count_out == NULL) {
        return false;
    }

    *frequencies = NULL;
    *frequency_count_out = 0;

    if (list_count > 0 && lists == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].length > 0 && lists[i].values == NULL) {
            return false;
        }

        if (lists[i].length > SIZE_MAX - total) {
            return false;
        }

        total += lists[i].length;
    }

    if (total == 0) {
        return true;
    }

    if (total > SIZE_MAX / sizeof(*values)) {
        return false;
    }

    values = malloc(total * sizeof(*values));
    if (values == NULL) {
        return false;
    }

    for (size_t i = 0; i < list_count; ++i) {
        for (size_t j = 0; j < lists[i].length; ++j) {
            values[offset++] = lists[i].values[j];
        }
    }

    qsort(values, total, sizeof(*values), compare_ints);

    unique_count = 1;
    for (size_t i = 1; i < total; ++i) {
        if (values[i] != values[i - 1]) {
            ++unique_count;
        }
    }

    if (unique_count > SIZE_MAX / sizeof(*result)) {
        free(values);
        return false;
    }

    result = malloc(unique_count * sizeof(*result));
    if (result == NULL) {
        free(values);
        return false;
    }

    size_t result_index = 0;
    size_t count = 1;

    for (size_t i = 1; i <= total; ++i) {
        if (i < total && values[i] == values[i - 1]) {
            ++count;
        } else {
            result[result_index].value = values[i - 1];
            result[result_index].count = count;
            ++result_index;
            count = 1;
        }
    }

    free(values);
    *frequencies = result;
    *frequency_count_out = unique_count;
    return true;
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
    size_t frequency_count_result = 0;

    if (!frequency_count(lists, sizeof(lists) / sizeof(lists[0]),
                         &frequencies, &frequency_count_result)) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < frequency_count_result; ++i) {
        if (printf("%d: %zu\n", frequencies[i].value,
                   frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}