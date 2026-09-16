#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

static int compare_ints(const void *a, const void *b)
{
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    return (x > y) - (x < y);
}

static int find_frequencies(const int *const *lists,
                            const size_t *lengths,
                            size_t list_count,
                            Frequency **frequencies,
                            size_t *frequency_count)
{
    size_t total = 0;
    size_t position = 0;
    int *elements = NULL;
    Frequency *result = NULL;

    if (lists == NULL || lengths == NULL ||
        frequencies == NULL || frequency_count == NULL) {
        return -1;
    }

    *frequencies = NULL;
    *frequency_count = 0;

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

    if (total > SIZE_MAX / sizeof(*elements)) {
        return -1;
    }

    elements = malloc(total * sizeof(*elements));
    if (elements == NULL) {
        return -1;
    }

    for (size_t i = 0; i < list_count; ++i) {
        for (size_t j = 0; j < lengths[i]; ++j) {
            elements[position++] = lists[i][j];
        }
    }

    qsort(elements, total, sizeof(*elements), compare_ints);

    if (total > SIZE_MAX / sizeof(*result)) {
        free(elements);
        return -1;
    }

    result = malloc(total * sizeof(*result));
    if (result == NULL) {
        free(elements);
        return -1;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < total; ++i) {
        if (unique_count == 0 ||
            result[unique_count - 1].value != elements[i]) {
            result[unique_count].value = elements[i];
            result[unique_count].count = 1;
            ++unique_count;
        } else {
            ++result[unique_count - 1].count;
        }
    }

    free(elements);
    *frequencies = result;
    *frequency_count = unique_count;

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
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    Frequency *frequencies = NULL;
    size_t frequency_count = 0;

    if (find_frequencies(lists, lengths, list_count,
                         &frequencies, &frequency_count) != 0) {
        fputs("Failed to calculate frequencies.\n", stderr);
        free(frequencies);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        if (printf("%d: %zu\n",
                   frequencies[i].value,
                   frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}