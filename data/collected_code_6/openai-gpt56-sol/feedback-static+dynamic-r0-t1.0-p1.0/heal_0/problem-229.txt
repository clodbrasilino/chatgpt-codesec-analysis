#include <stdio.h>
#include <stdlib.h>

static void rearrange(int array[], size_t length)
{
    size_t next_negative = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] < 0) {
            int temp = array[next_negative];
            array[next_negative] = array[i];
            array[i] = temp;
            ++next_negative;
        }
    }
}

int main(void)
{
    size_t length;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", length) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    rearrange(array, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1 == length ? "\n" : " ") < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);
    return EXIT_SUCCESS;
}