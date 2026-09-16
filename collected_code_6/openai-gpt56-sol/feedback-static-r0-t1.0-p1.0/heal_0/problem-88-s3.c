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
    size_t index = 0;

    if (count == NULL || (list == NULL && length != 0U)) {
        return NULL;
    }

    *count = 0;

    if (length == 0U) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return NULL;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        sorted[index] = list[index];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    unique_count = 1;
    for (index = 1; index < length; ++index) {
        if (sorted[index] != sorted[index - 1]) {
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

    *count = 0;
    for (index = 0; index < length; ++index) {
        if (*count == 0U ||
            frequencies[*count - 1U].value != sorted[index]) {
            frequencies[*count].value = sorted[index];
            frequencies[*count].frequency = 1U;
            ++(*count);
        } else {
            ++frequencies[*count - 1U].frequency;
        }
    }

    free(sorted);
    return frequencies;
}

int main(void)
{
    int list[] = {4, 2, 4, 3, 2, 4, 1, 3};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t count = 0;
    size_t index = 0;
    Frequency *frequencies = get_frequencies(list, length, &count);

    if (length != 0U && frequencies == NULL) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (printf("%d: %zu\n",
                   frequencies[index].value,
                   frequencies[index].frequency) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}