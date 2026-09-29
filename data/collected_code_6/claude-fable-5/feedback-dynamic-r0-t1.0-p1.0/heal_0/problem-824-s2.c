#include <stdio.h>
#include <stdlib.h>

int remove_even_numbers(const int *input, size_t input_size, int **output, size_t *output_size)
{
    size_t count = 0;
    size_t i;
    int *result = NULL;

    if (input == NULL || output == NULL || output_size == NULL) {
        return -1;
    }

    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
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
        return -1;
    }

    count = 0;
    for (i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            result[count] = input[i];
            count++;
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
    int *odd_numbers = NULL;
    size_t odd_size = 0;
    size_t i;

    if (remove_even_numbers(numbers, numbers_size, &odd_numbers, &odd_size) != 0) {
        fprintf(stderr, "Error: failed to remove even numbers\n");
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    for (i = 0; i < numbers_size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("List without even numbers: ");
    for (i = 0; i < odd_size; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free(odd_numbers);
    odd_numbers = NULL;

    return EXIT_SUCCESS;
}