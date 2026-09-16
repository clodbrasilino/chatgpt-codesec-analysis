#include <stdio.h>
#include <stdlib.h>

static int rearrange_alternating(int *array, size_t length)
{
    int *result;
    size_t positive = 0;
    size_t negative = 0;
    size_t output = 0;
    int want_positive = 1;

    if (array == NULL && length != 0) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    while (output < length) {
        size_t index = want_positive ? positive : negative;
        int found = 0;

        while (index < length) {
            if ((want_positive && array[index] >= 0) ||
                (!want_positive && array[index] < 0)) {
                result[output++] = array[index];
                index++;
                found = 1;
                break;
            }
            index++;
        }

        if (want_positive) {
            positive = index;
        } else {
            negative = index;
        }

        if (found) {
            want_positive = !want_positive;
            continue;
        }

        index = want_positive ? negative : positive;

        while (index < length) {
            if ((!want_positive && array[index] >= 0) ||
                (want_positive && array[index] < 0)) {
                result[output++] = array[index];
            }
            index++;
        }

        break;
    }

    for (size_t i = 0; i < length; i++) {
        array[i] = result[i];
    }

    free(result);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, -4, -1, 4, -6, 7, -8};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (rearrange_alternating(array, length) != 0) {
        fputs("Failed to rearrange the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        if (printf("%d%s", array[i], i + 1 < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}