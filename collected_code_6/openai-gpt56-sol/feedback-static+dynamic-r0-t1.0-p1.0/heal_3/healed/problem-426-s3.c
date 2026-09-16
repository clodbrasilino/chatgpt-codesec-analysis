#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    if (output_size == NULL) {
        return NULL;
    }

    *output_size = 0;

    if (input == NULL && input_size != 0) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < input_size; ++i) {
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

    for (size_t i = 0; i < input_size; ++i) {
        if (input[i] % 2 != 0) {
            output[output_index++] = input[i];
        }
    }

    *output_size = output_index;
    return output;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;

    int *odd_numbers =
        filter_odd_numbers(numbers, number_count, &odd_count);

    if (odd_numbers == NULL && odd_count != 0) {
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

    if (putchar('\n') == EOF) {
        free(odd_numbers);
        return EXIT_FAILURE;
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}