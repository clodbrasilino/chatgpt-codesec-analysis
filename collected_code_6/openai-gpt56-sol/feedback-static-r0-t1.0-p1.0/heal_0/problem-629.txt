#include <stdio.h>
#include <stdlib.h>

static int *find_even_numbers(const int *numbers, size_t count, size_t *even_count)
{
    int *even_numbers = NULL;
    size_t found = 0;

    if (even_count == NULL || (numbers == NULL && count != 0U)) {
        return NULL;
    }

    *even_count = 0U;

    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            ++found;
        }
    }

    if (found == 0U) {
        return NULL;
    }

    if (found > SIZE_MAX / sizeof(*even_numbers)) {
        return NULL;
    }

    even_numbers = malloc(found * sizeof(*even_numbers));
    if (even_numbers == NULL) {
        return NULL;
    }

    size_t index = 0U;
    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            even_numbers[index++] = numbers[i];
        }
    }

    *even_count = found;
    return even_numbers;
}

int main(void)
{
    const int numbers[] = {7, 2, -4, 9, 12, 15, 0, 21, 28};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_count = 0U;
    int *even_numbers = find_even_numbers(numbers, count, &even_count);

    if (even_numbers == NULL && even_count == 0U) {
        for (size_t i = 0U; i < count; ++i) {
            if (numbers[i] % 2 == 0) {
                fputs("Unable to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }
        }

        puts("No even numbers found.");
        return EXIT_SUCCESS;
    }

    for (size_t i = 0U; i < even_count; ++i) {
        if (printf("%d%s", even_numbers[i],
                   i + 1U < even_count ? " " : "\n") < 0) {
            free(even_numbers);
            return EXIT_FAILURE;
        }
    }

    free(even_numbers);
    return EXIT_SUCCESS;
}