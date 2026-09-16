#include <stdio.h>
#include <stdlib.h>

static int is_greater_than_all(int number, const int *array, size_t length)
{
    if (array == NULL && length != 0U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (number <= array[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    size_t length = 0U;
    int number = 0;
    int *array = NULL;

    if (printf("Enter the number of array elements: ") < 0 ||
        scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Array size is too large.\n");
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
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
    }

    if (printf("Enter the number to check: ") < 0 ||
        scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid number.\n");
        free(array);
        return EXIT_FAILURE;
    }

    if (is_greater_than_all(number, array, length)) {
        printf("%d is greater than every array element.\n", number);
    } else {
        printf("%d is not greater than every array element.\n", number);
    }

    free(array);
    return EXIT_SUCCESS;
}