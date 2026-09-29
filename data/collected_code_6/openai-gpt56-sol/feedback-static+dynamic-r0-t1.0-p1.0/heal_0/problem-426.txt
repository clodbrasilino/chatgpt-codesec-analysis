#include <stdio.h>
#include <stdlib.h>

static int filter_odd_numbers(const int *input, size_t input_count,
                              int **output, size_t *output_count)
{
    int *result = NULL;
    size_t count = 0;
    size_t index = 0;

    if (input == NULL || output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] % 2 != 0) {
            ++count;
        }
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] % 2 != 0) {
            result[index++] = input[i];
        }
    }

    *output = result;
    *output_count = count;
    return 0;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    int *odd_numbers = NULL;
    size_t odd_count = 0;

    if (filter_odd_numbers(numbers, number_count, &odd_numbers, &odd_count) != 0) {
        fputs("Failed to filter odd numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < odd_count; ++i) {
        if (printf("%d%s", odd_numbers[i], i + 1 < odd_count ? " " : "\n") < 0) {
            free(odd_numbers);
            return EXIT_FAILURE;
        }
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}