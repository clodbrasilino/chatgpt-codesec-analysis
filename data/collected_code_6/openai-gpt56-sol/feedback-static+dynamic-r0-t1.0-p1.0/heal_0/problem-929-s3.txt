#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} ItemCount;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int count_repeated_items(const int *tuple, size_t length,
                                ItemCount **repeated, size_t *repeated_count)
{
    int *sorted = NULL;
    ItemCount *result = NULL;
    size_t result_count = 0;

    if (repeated == NULL || repeated_count == NULL ||
        (tuple == NULL && length != 0)) {
        return -1;
    }

    *repeated = NULL;
    *repeated_count = 0;

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        sorted[i] = tuple[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0; i < length;) {
        size_t next = i + 1;

        while (next < length && sorted[next] == sorted[i]) {
            ++next;
        }

        if (next - i > 1) {
            ++result_count;
        }

        i = next;
    }

    if (result_count != 0) {
        if (result_count > SIZE_MAX / sizeof(*result)) {
            free(sorted);
            return -1;
        }

        result = malloc(result_count * sizeof(*result));
        if (result == NULL) {
            free(sorted);
            return -1;
        }

        size_t output_index = 0;

        for (size_t i = 0; i < length;) {
            size_t next = i + 1;

            while (next < length && sorted[next] == sorted[i]) {
                ++next;
            }

            if (next - i > 1) {
                result[output_index].value = sorted[i];
                result[output_index].count = next - i;
                ++output_index;
            }

            i = next;
        }
    }

    free(sorted);
    *repeated = result;
    *repeated_count = result_count;

    return 0;
}

int main(void)
{
    const int tuple[] = {4, 2, 7, 4, 2, 2, 9, 7, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    ItemCount *repeated = NULL;
    size_t repeated_count = 0;

    if (count_repeated_items(tuple, length, &repeated, &repeated_count) != 0) {
        fputs("Unable to count repeated items.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < repeated_count; ++i) {
        if (printf("%d: %zu\n", repeated[i].value, repeated[i].count) < 0) {
            free(repeated);
            return EXIT_FAILURE;
        }
    }

    free(repeated);
    return EXIT_SUCCESS;
}