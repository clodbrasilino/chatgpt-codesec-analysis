#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t length, size_t *output_length)
{
    if (output_length == NULL) {
        return NULL;
    }

    *output_length = 0;

    if (input == NULL && length > 0) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            ++count;
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *output = malloc(count * sizeof(*output));
    if (output == NULL) {
        return NULL;
    }

    size_t output_index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            output[output_index++] = input[i];
        }
    }

    *output_length = output_index;
    return output;
}

int main(void)
{
    size_t length = 0;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *numbers = NULL;

    if (length > 0) {
        numbers = malloc(length * sizeof(*numbers));
        if (numbers == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &numbers[i]) != 1) {
                free(numbers);
                return EXIT_FAILURE;
            }
        }
    }

    size_t odd_count = 0;
    int *odd_numbers = filter_odd_numbers(numbers, length, &odd_count);

    free(numbers);

    if (length > 0 && odd_count == 0 && odd_numbers == NULL) {
        return EXIT_SUCCESS;
    }

    if (odd_numbers == NULL && odd_count > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < odd_count; ++i) {
        if (i > 0 && printf(" ") < 0) {
            free(odd_numbers);
            return EXIT_FAILURE;
        }

        if (printf("%d", odd_numbers[i]) < 0) {
            free(odd_numbers);
            return EXIT_FAILURE;
        }
    }

    if (odd_count > 0 && printf("\n") < 0) {
        free(odd_numbers);
        return EXIT_FAILURE;
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}