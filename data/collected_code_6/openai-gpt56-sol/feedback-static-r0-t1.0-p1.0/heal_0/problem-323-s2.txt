#include <stdio.h>
#include <stdlib.h>

static int rearrange_alternating(int *array, size_t length)
{
    int *result;
    size_t positive = 0;
    size_t negative = 0;
    size_t output = 0;
    int want_positive;

    if (array == NULL && length != 0) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    want_positive = array[0] >= 0;

    while (output < length) {
        size_t *index = want_positive ? &positive : &negative;

        while (*index < length &&
               (want_positive ? array[*index] < 0 : array[*index] >= 0)) {
            ++(*index);
        }

        if (*index < length) {
            result[output++] = array[(*index)++];
            want_positive = !want_positive;
            continue;
        }

        index = want_positive ? &negative : &positive;

        while (*index < length &&
               (want_positive ? array[*index] >= 0 : array[*index] < 0)) {
            ++(*index);
        }

        while (*index < length) {
            result[output++] = array[(*index)++];

            while (*index < length &&
                   (want_positive ? array[*index] >= 0 : array[*index] < 0)) {
                ++(*index);
            }
        }
    }

    for (size_t i = 0; i < length; ++i) {
        array[i] = result[i];
    }

    free(result);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, -4, -1, 4, -6, -7, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (rearrange_alternating(array, length) != 0) {
        fputs("Failed to rearrange the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", array[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}