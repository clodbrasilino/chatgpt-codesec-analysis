#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t length, size_t *output_length)
{
    if (output_length == NULL) {
        return NULL;
    }

    *output_length = 0;

    if (input == NULL && length != 0) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            ++count;
        }
    }

    if (count == 0 || count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *output = malloc(count * sizeof(*output));
    if (output == NULL) {
        return NULL;
    }

    size_t index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            output[index++] = input[i];
        }
    }

    *output_length = count;
    return output;
}

int main(void)
{
    int *numbers = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int value;

    while (scanf("%d", &value) == 1) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*numbers)) {
                free(numbers);
                return EXIT_FAILURE;
            }

            int *resized = realloc(numbers, new_capacity * sizeof(*numbers));
            if (resized == NULL) {
                free(numbers);
                return EXIT_FAILURE;
            }

            numbers = resized;
            capacity = new_capacity;
        }

        numbers[length++] = value;
    }

    size_t odd_count = 0;
    int *odd_numbers = filter_odd_numbers(numbers, length, &odd_count);

    if (odd_numbers == NULL && odd_count == 0) {
        for (size_t i = 0; i < length; ++i) {
            if (numbers[i] % 2 != 0) {
                free(numbers);
                return EXIT_FAILURE;
            }
        }
    }

    free(numbers);

    for (size_t i = 0; i < odd_count; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", odd_numbers[i]);
    }

    putchar('\n');
    free(odd_numbers);

    return EXIT_SUCCESS;
}