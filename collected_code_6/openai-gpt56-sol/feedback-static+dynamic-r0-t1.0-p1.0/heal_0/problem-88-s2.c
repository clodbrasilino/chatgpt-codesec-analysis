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
    int *sorted = NULL;
    Frequency *frequencies = NULL;
    size_t unique_count = 0;
    size_t i = 0;

    if (count == NULL) {
        return NULL;
    }

    *count = 0;

    if (length == 0) {
        return NULL;
    }

    if (list == NULL || length > SIZE_MAX / sizeof(*sorted)) {
        return NULL;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        sorted[i] = list[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    unique_count = 1;
    for (i = 1; i < length; ++i) {
        if (sorted[i] != sorted[i - 1]) {
            ++unique_count;
        }
    }

    if (unique_count > SIZE_MAX / sizeof(*frequencies)) {
        free(sorted);
        return NULL;
    }

    frequencies = malloc(unique_count * sizeof(*frequencies));
    if (frequencies == NULL) {
        free(sorted);
        return NULL;
    }

    frequencies[0].value = sorted[0];
    frequencies[0].frequency = 1;
    unique_count = 0;

    for (i = 1; i < length; ++i) {
        if (sorted[i] == frequencies[unique_count].value) {
            ++frequencies[unique_count].frequency;
        } else {
            ++unique_count;
            frequencies[unique_count].value = sorted[i];
            frequencies[unique_count].frequency = 1;
        }
    }

    *count = unique_count + 1;
    free(sorted);
    return frequencies;
}

int main(void)
{
    const int list[] = {4, 2, 4, 3, 2, 4, 1, 3, 2};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t count = 0;
    size_t i = 0;
    Frequency *frequencies = get_frequencies(list, length, &count);

    if (length != 0 && frequencies == NULL) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
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