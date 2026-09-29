#include <stdio.h>
#include <stdlib.h>

static int *find_odd_numbers(const int *numbers, size_t count, size_t *odd_count)
{
    int *odd_numbers = NULL;
    size_t found = 0;
    size_t i;

    if (odd_count == NULL || (numbers == NULL && count != 0)) {
        return NULL;
    }

    *odd_count = 0;

    for (i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            ++found;
        }
    }

    if (found == 0) {
        return NULL;
    }

    if (found > SIZE_MAX / sizeof(*odd_numbers)) {
        return NULL;
    }

    odd_numbers = malloc(found * sizeof(*odd_numbers));
    if (odd_numbers == NULL) {
        return NULL;
    }

    found = 0;
    for (i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            odd_numbers[found++] = numbers[i];
        }
    }

    *odd_count = found;
    return odd_numbers;
}

int main(void)
{
    const int numbers[] = {12, 7, -3, 8, 0, 15, 22, 9, -4};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    int *odd_numbers = find_odd_numbers(numbers, count, &odd_count);
    size_t i;

    if (odd_numbers == NULL && odd_count == 0) {
        for (i = 0; i < count; ++i) {
            if (numbers[i] % 2 != 0) {
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }
        }

        puts("No odd numbers found.");
        return EXIT_SUCCESS;
    }

    for (i = 0; i < odd_count; ++i) {
        printf("%d%s", odd_numbers[i], i + 1 == odd_count ? "\n" : " ");
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}