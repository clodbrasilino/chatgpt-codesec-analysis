#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int filter_even(const int *input, size_t input_size, int **output, size_t *output_size)
{
    size_t count;
    size_t i;
    size_t j;
    int *result;

    if (input == NULL || output == NULL || output_size == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        *output = NULL;
        *output_size = 0;
        return 0;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        *output = NULL;
        *output_size = 0;
        return -1;
    }

    j = 0;
    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            result[j] = input[i];
            j++;
        }
    }

    *output = result;
    *output_size = count;
    return 0;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t numbers_size = sizeof(numbers) / sizeof(numbers[0]);
    int *evens = NULL;
    size_t evens_size = 0;
    size_t i;

    if (filter_even(numbers, numbers_size, &evens, &evens_size) != 0) {
        fprintf(stderr, "Error: failed to filter even numbers\n");
        return EXIT_FAILURE;
    }

    if (evens_size == 0) {
        printf("No even numbers found\n");
    } else {
        printf("Even numbers:");
        for (i = 0; i < evens_size; i++) {
            printf(" %d", evens[i]);
        }
        printf("\n");
    }

    free(evens);
    evens = NULL;

    return EXIT_SUCCESS;
}