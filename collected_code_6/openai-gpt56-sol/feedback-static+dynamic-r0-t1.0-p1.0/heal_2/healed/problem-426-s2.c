#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *filter_odd_numbers(const int *input, size_t length, size_t *output_length)
{
    size_t count = 0;
    size_t index = 0;
    int *output;

    if (output_length == NULL) {
        return NULL;
    }

    *output_length = 0;

    if (input == NULL && length != 0) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            ++count;
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*output)) {
        return NULL;
    }

    output = malloc(count * sizeof(*output));
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (input[i] % 2 != 0) {
            output[index++] = input[i];
        }
    }

    *output_length = index;
    return output;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    int *odd_numbers = filter_odd_numbers(numbers, number_count, &odd_count);

    if (odd_numbers == NULL && odd_count != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < odd_count; ++i) {
        if (printf("%d%s", odd_numbers[i],
                   i + 1 < odd_count ? " " : "\n") < 0) {
            free(odd_numbers);
            return EXIT_FAILURE;
        }
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}