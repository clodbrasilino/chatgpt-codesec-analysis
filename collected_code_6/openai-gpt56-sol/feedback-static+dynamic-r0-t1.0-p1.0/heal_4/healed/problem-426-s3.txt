#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t input_size, size_t *output_size)
{
    if (output_size == NULL) {
        return NULL;
    }

    *output_size = 0;

    if (input == NULL) {
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
    int *numbers = NULL;
    size_t number_count = 0;
    size_t capacity = 0;
    int value;

    while (scanf("%d", &value) == 1) {
        if (number_count == capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*numbers)) {
                free(numbers);
                return EXIT_FAILURE;
            }

            int *new_numbers =
                realloc(numbers, new_capacity * sizeof(*numbers));

            if (new_numbers == NULL) {
                free(numbers);
                return EXIT_FAILURE;
            }

            numbers = new_numbers;
            capacity = new_capacity;
        }

        numbers[number_count++] = value;
    }

    if (!feof(stdin)) {
        free(numbers);
        return EXIT_FAILURE;
    }

    size_t odd_count = 0;
    int *odd_numbers =
        filter_odd_numbers(numbers, number_count, &odd_count);

    free(numbers);

    if (odd_numbers == NULL && odd_count != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < odd_count; ++i) {
        if (i > 0 && putchar(' ') == EOF) {
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