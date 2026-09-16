#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int find_difference(const int *numbers, size_t count, int *difference)
{
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    if (numbers == NULL || difference == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count && (!even_found || !odd_found); ++i) {
        if (numbers[i] % 2 == 0) {
            if (!even_found) {
                first_even = numbers[i];
                even_found = 1;
            }
        } else if (!odd_found) {
            first_odd = numbers[i];
            odd_found = 1;
        }
    }

    if (!even_found || !odd_found) {
        return 0;
    }

    *difference = first_even - first_odd;
    return 1;
}

int main(void)
{
    size_t count = 0;
    int *numbers = NULL;
    int difference = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid list size.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid list element.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (!find_difference(numbers, count, &difference)) {
        fprintf(stderr, "The list must contain an even and an odd number.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%d\n", difference);
    free(numbers);
    return EXIT_SUCCESS;
}