#include <stdio.h>
#include <stdlib.h>

static int rearrange_numbers(int *array, size_t length)
{
    int *temporary;
    size_t output_index = 0;

    if (array == NULL && length != 0) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] < 0) {
            temporary[output_index++] = array[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] >= 0) {
            temporary[output_index++] = array[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        array[i] = temporary[i];
    }

    free(temporary);
    return 0;
}

int main(void)
{
    int numbers[] = {12, -7, 5, -3, 0, -11, 8, -1};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);

    if (rearrange_numbers(numbers, length) != 0) {
        fputs("Failed to rearrange the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", numbers[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}