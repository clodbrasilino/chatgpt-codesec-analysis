#include <stdio.h>
#include <stdlib.h>

int sum_first_even_and_odd(const int *numbers, size_t count, int *sum)
{
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (numbers == NULL || sum == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (numbers[i] % 2 == 0) {
            if (!found_even) {
                first_even = numbers[i];
                found_even = 1;
            }
        } else if (!found_odd) {
            first_odd = numbers[i];
            found_odd = 1;
        }
    }

    if (!found_even || !found_odd) {
        return 0;
    }

    *sum = first_even + first_odd;
    return 1;
}

int main(void)
{
    size_t count = 0;
    int *numbers = NULL;
    int sum = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*numbers)) {
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (!sum_first_even_and_odd(numbers, count, &sum)) {
        free(numbers);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", sum) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);
    return EXIT_SUCCESS;
}