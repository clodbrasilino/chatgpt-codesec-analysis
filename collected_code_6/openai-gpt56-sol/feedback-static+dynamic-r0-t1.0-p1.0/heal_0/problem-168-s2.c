#include <stdio.h>
#include <stdlib.h>

size_t find_frequency(const int array[], size_t length, int target)
{
    size_t frequency = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == target) {
            ++frequency;
        }
    }

    return frequency;
}

int main(void)
{
    size_t length;
    int target;

    if (printf("Enter the number of elements: ") < 0 ||
        scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Array size is too large.\n");
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    if (printf("Enter %zu integers: ", length) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (printf("Enter the number to find: ") < 0 ||
        scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid target number.\n");
        free(array);
        return EXIT_FAILURE;
    }

    size_t frequency = find_frequency(array, length, target);

    if (printf("%d occurs %zu time%s.\n",
               target,
               frequency,
               frequency == 1 ? "" : "s") < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}