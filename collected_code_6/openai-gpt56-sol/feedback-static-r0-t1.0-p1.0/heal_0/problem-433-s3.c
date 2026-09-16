#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_greater_than_all(int number, const int *array, size_t length)
{
    if (array == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (number <= array[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t length = 0U;

    if (printf("Enter the number of array elements: ") < 0 ||
        scanf("%zu", &length) != 1 ||
        length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid array size.\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu array elements: ", length) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    int number = 0;

    if (printf("Enter the number to check: ") < 0 ||
        scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid number.\n");
        free(array);
        return EXIT_FAILURE;
    }

    const bool result = is_greater_than_all(number, array, length);

    if (printf("%s\n", result
               ? "The number is greater than all array elements."
               : "The number is not greater than all array elements.") < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}