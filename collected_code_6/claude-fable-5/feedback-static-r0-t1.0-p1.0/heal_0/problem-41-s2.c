#include <stdio.h>
#include <stdlib.h>

int *filter_even(const int *input, size_t input_size, size_t *output_size)
{
    if (input == NULL || output_size == NULL) {
        return NULL;
    }

    *output_size = 0;

    if (input_size == 0) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            result[j] = input[i];
            j++;
        }
    }

    *output_size = count;
    return result;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t numbers_size = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_count = 0;

    int *evens = filter_even(numbers, numbers_size, &even_count);

    if (evens == NULL && even_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Even numbers: ");
    for (size_t i = 0; i < even_count; i++) {
        printf("%d ", evens[i]);
    }
    printf("\n");

    free(evens);
    evens = NULL;

    return EXIT_SUCCESS;
}