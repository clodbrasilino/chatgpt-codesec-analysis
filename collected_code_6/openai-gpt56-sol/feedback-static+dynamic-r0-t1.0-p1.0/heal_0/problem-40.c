#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t frequency;
} Frequency;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int find_frequencies(const int *const *lists,
                            const size_t *lengths,
                            size_t list_count,
                            Frequency **result,
                            size_t *result_count)
{
    size_t total = 0;
    size_t offset = 0;
    size_t unique_count = 0;
    int *values = NULL;
    Frequency *frequencies = NULL;

    if (result == NULL || result_count == NULL ||
        (list_count > 0 && (lists == NULL || lengths == NULL))) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < list_count; ++i) {
        if (lengths[i] > 0 && lists[i] == NULL) {
            return -1;
        }
        if (lengths[i] > SIZE_MAX - total) {
            return -1;
        }
        total += lengths[i];
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
        for (size_t j = 0; j < lengths[i]; ++j) {
            values[offset++] = lists[i][j];
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

    size_t index = 0;
    frequencies[index].value = values[0];
    frequencies[index].frequency = 1;

    for (size_t i = 1; i < total; ++i) {
        if (values[i] == frequencies[index].value) {
            ++frequencies[index].frequency;
        } else {
            ++index;
            frequencies[index].value = values[i];
            frequencies[index].frequency = 1;
        }
    }

    free(values);
    *result = frequencies;
    *result_count = unique_count;

    return 0;
}

int main(void)
{
    const int list1[] = {1, 2, 2, 3};
    const int list2[] = {2, 3, 4};
    const int list3[] = {1, 4, 4, 5};
    const int *lists[] = {list1, list2, list3};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };
    Frequency *frequencies = NULL;
    size_t frequency_count = 0;

    if (find_frequencies(lists,
                         lengths,
                         sizeof(lists) / sizeof(lists[0]),
                         &frequencies,
                         &frequency_count) != 0) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        if (printf("%d: %zu\n",
                   frequencies[i].value,
                   frequencies[i].frequency) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}