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

static Frequency *find_frequencies(const int *values, size_t count,
                                   size_t *frequency_count)
{
    int *sorted;
    Frequency *frequencies;
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (frequency_count == NULL) {
        return NULL;
    }

    *frequency_count = 0;

    if (values == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*frequencies)) {
        return NULL;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (i = 0; i < count; ++i) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            ++unique_count;
        }
    }

    frequencies = malloc(unique_count * sizeof(*frequencies));
    if (frequencies == NULL) {
        free(sorted);
        return NULL;
    }

    i = 0;
    j = 0;
    while (i < count) {
        size_t end = i + 1;

        while (end < count && sorted[end] == sorted[i]) {
            ++end;
        }

        frequencies[j].value = sorted[i];
        frequencies[j].frequency = end - i;
        ++j;
        i = end;
    }

    free(sorted);
    *frequency_count = unique_count;
    return frequencies;
}

int main(void)
{
    int values[] = {4, 2, 4, 3, 2, 4, 1, 3};
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t frequency_count;
    Frequency *frequencies;
    size_t i;

    frequencies = find_frequencies(values, count, &frequency_count);
    if (frequencies == NULL) {
        fputs("Unable to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < frequency_count; ++i) {
        if (printf("%d: %zu\n", frequencies[i].value,
                   frequencies[i].frequency) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}