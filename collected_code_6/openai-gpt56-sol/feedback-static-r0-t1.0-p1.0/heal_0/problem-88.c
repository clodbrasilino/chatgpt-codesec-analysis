#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t frequency;
} Frequency;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static Frequency *get_frequencies(const int *list, size_t length, size_t *count)
{
    int *sorted;
    Frequency *frequencies;
    size_t unique_count = 0U;
    size_t i;
    size_t index;

    if (count == NULL) {
        return NULL;
    }

    *count = 0U;

    if (length == 0U) {
        return NULL;
    }

    if (list == NULL ||
        length > SIZE_MAX / sizeof(*sorted) ||
        length > SIZE_MAX / sizeof(*frequencies)) {
        return NULL;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        sorted[i] = list[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    unique_count = 1U;
    for (i = 1U; i < length; ++i) {
        if (sorted[i] != sorted[i - 1U]) {
            ++unique_count;
        }
    }

    frequencies = malloc(unique_count * sizeof(*frequencies));
    if (frequencies == NULL) {
        free(sorted);
        return NULL;
    }

    index = 0U;
    frequencies[index].value = sorted[0];
    frequencies[index].frequency = 1U;

    for (i = 1U; i < length; ++i) {
        if (sorted[i] == frequencies[index].value) {
            ++frequencies[index].frequency;
        } else {
            ++index;
            frequencies[index].value = sorted[i];
            frequencies[index].frequency = 1U;
        }
    }

    free(sorted);
    *count = unique_count;
    return frequencies;
}

int main(void)
{
    int list[] = {4, 2, 7, 2, 4, 4, 9, 7, 2};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t count;
    size_t i;
    Frequency *frequencies = get_frequencies(list, length, &count);

    if (length != 0U && frequencies == NULL) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
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