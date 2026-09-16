#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void shell_sort(int *array, size_t length)
{
    size_t gap;
    size_t i;
    size_t j;
    int temp;

    if (array == NULL || length < 2U) {
        return;
    }

    for (gap = length / 2U; gap > 0U; gap /= 2U) {
        for (i = gap; i < length; i++) {
            temp = array[i];
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

int main(void)
{
    int *array = NULL;
    size_t length = 0U;
    size_t i;
    int input_value;

    if (printf("Enter number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid input for array length\n");
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        fprintf(stderr, "Array length must be greater than zero\n");
        return EXIT_FAILURE;
    }

    if (length > (SIZE_MAX / sizeof(int))) {
        fprintf(stderr, "Array length too large\n");
        return EXIT_FAILURE;
    }

    array = (int *)malloc(length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", length) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; i++) {
        if (scanf("%d", &input_value) != 1) {
            fprintf(stderr, "Invalid input for array element\n");
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = input_value;
    }

    shell_sort(array, length);

    if (printf("Sorted array: ") < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; i++) {
        if (printf("%d ", array[i]) < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}