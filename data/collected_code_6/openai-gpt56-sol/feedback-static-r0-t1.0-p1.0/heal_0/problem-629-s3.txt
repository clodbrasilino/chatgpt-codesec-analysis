#include <stdio.h>
#include <stdlib.h>

static int *find_even_numbers(const int *numbers, size_t count, size_t *even_count)
{
    int *even_numbers = NULL;
    size_t matches = 0;
    size_t index = 0;

    if (even_count == NULL || (numbers == NULL && count != 0)) {
        return NULL;
    }

    *even_count = 0;

    for (index = 0; index < count; ++index) {
        if (numbers[index] % 2 == 0) {
            ++matches;
        }
    }

    if (matches == 0) {
        return NULL;
    }

    if (matches > SIZE_MAX / sizeof(*even_numbers)) {
        return NULL;
    }

    even_numbers = malloc(matches * sizeof(*even_numbers));
    if (even_numbers == NULL) {
        return NULL;
    }

    matches = 0;

    for (index = 0; index < count; ++index) {
        if (numbers[index] % 2 == 0) {
            even_numbers[matches++] = numbers[index];
        }
    }

    *even_count = matches;
    return even_numbers;
}

int main(void)
{
    const int numbers[] = {7, 2, 13, 8, 4, 11, 20, 5};
    const size_t number_count = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_count = 0;
    size_t index = 0;
    int *even_numbers = find_even_numbers(numbers, number_count, &even_count);

    if (even_count > 0 && even_numbers == NULL) {
        fputs("Failed to find even numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < even_count; ++index) {
        if (printf("%d%s", even_numbers[index],
                   index + 1 == even_count ? "\n" : " ") < 0) {
            free(even_numbers);
            return EXIT_FAILURE;
        }
    }

    if (even_count == 0 && puts("No even numbers found.") == EOF) {
        free(even_numbers);
        return EXIT_FAILURE;
    }

    free(even_numbers);
    return EXIT_SUCCESS;
}