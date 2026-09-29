#include <stdio.h>
#include <stdlib.h>

static int filter_even_numbers(const int *input, size_t input_count,
                               int **output, size_t *output_count)
{
    int *result = NULL;
    size_t count = 0;
    size_t index = 0;

    if (output == NULL || output_count == NULL ||
        (input == NULL && input_count != 0)) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    for (index = 0; index < input_count; ++index) {
        if (input[index] % 2 == 0) {
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

    count = 0;
    for (index = 0; index < input_count; ++index) {
        if (input[index] % 2 == 0) {
            result[count++] = input[index];
        }
    }

    *output = result;
    *output_count = count;
    return 0;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    int *even_numbers = NULL;
    size_t even_count = 0;
    size_t index = 0;

    if (filter_even_numbers(numbers, number_count,
                            &even_numbers, &even_count) != 0) {
        fputs("Failed to filter even numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < even_count; ++index) {
        if (printf("%d%s", even_numbers[index],
                   index + 1 == even_count ? "\n" : " ") < 0) {
            free(even_numbers);
            return EXIT_FAILURE;
        }
    }

    if (even_count == 0 && putchar('\n') == EOF) {
        free(even_numbers);
        return EXIT_FAILURE;
    }

    free(even_numbers);
    return EXIT_SUCCESS;
}