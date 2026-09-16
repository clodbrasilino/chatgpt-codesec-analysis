#include <stdio.h>
#include <stdlib.h>

static int rearrange_numbers(int *array, size_t length)
{
    int *temporary;
    size_t output_index = 0;

    if (array == NULL && length != 0U) {
        return -1;
    }

    if (length == 0U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    for (size_t index = 0; index < length; ++index) {
        if (array[index] < 0) {
            temporary[output_index++] = array[index];
        }
    }

    for (size_t index = 0; index < length; ++index) {
        if (array[index] >= 0) {
            temporary[output_index++] = array[index];
        }
    }

    for (size_t index = 0; index < length; ++index) {
        array[index] = temporary[index];
    }

    free(temporary);
    return 0;
}

int main(void)
{
    int numbers[] = {1, -2, 3, -4, 0, 5, -6};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (rearrange_numbers(numbers, count) != 0) {
        fputs("Failed to rearrange the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", numbers[index]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}