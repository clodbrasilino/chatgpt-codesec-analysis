#include <stdio.h>
#include <stdlib.h>

static int find_greater_values(const int *list, size_t length, int threshold,
                               int **result, size_t *result_length)
{
    size_t count = 0;
    size_t index = 0;
    int *values = NULL;

    if (result == NULL || result_length == NULL ||
        (list == NULL && length != 0)) {
        return -1;
    }

    *result = NULL;
    *result_length = 0;

    for (size_t i = 0; i < length; ++i) {
        if (list[i] > threshold) {
            ++count;
        }
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] > threshold) {
            values[index++] = list[i];
        }
    }

    *result = values;
    *result_length = count;
    return 0;
}

int main(void)
{
    const int list[] = {3, 12, 7, 18, 2, 21, 9};
    const size_t length = sizeof(list) / sizeof(list[0]);
    const int threshold = 10;
    int *result = NULL;
    size_t result_length = 0;

    if (find_greater_values(list, length, threshold,
                            &result, &result_length) != 0) {
        fputs("Unable to find values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_length; ++i) {
        if (printf("%d\n", result[i]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}