#include <stdio.h>
#include <stdlib.h>

static int *find_even_numbers(const int *numbers, size_t count, size_t *even_count)
{
    int *even_numbers;
    size_t i;
    size_t found = 0;

    if (even_count == NULL || (numbers == NULL && count != 0)) {
        return NULL;
    }

    *even_count = 0;

    for (i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            ++found;
        }
    }

    if (found == 0) {
        return NULL;
    }

    if (found > SIZE_MAX / sizeof(*even_numbers)) {
        return NULL;
    }

    even_numbers = malloc(found * sizeof(*even_numbers));
    if (even_numbers == NULL) {
        return NULL;
    }

    found = 0;
    for (i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            even_numbers[found++] = numbers[i];
        }
    }

    *even_count = found;
    return even_numbers;
}

int main(void)
{
    const int numbers[] = {3, 8, -2, 7, 10, 15, 0, 21, 24};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_count = 0;
    int *even_numbers;
    size_t i;

    even_numbers = find_even_numbers(numbers, count, &even_count);

    if (even_numbers == NULL) {
        if (even_count == 0) {
            puts("No even numbers found.");
            return EXIT_SUCCESS;
        }

        fputs("Failed to find even numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < even_count; ++i) {
        printf("%d%s", even_numbers[i], i + 1 < even_count ? " " : "\n");
    }

    free(even_numbers);
    return EXIT_SUCCESS;
}