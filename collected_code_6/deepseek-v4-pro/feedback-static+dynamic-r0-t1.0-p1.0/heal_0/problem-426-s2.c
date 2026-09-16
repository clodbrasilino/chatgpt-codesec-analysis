#include <stdio.h>
#include <stdlib.h>

int *filter_odd(const int *input, size_t input_size, size_t *output_size) {
    if (input == NULL || output_size == NULL) {
        *output_size = 0;
        return NULL;
    }

    int *result = malloc(input_size * sizeof(int));
    if (result == NULL) {
        *output_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            result[count++] = input[i];
        }
    }

    if (count == 0) {
        free(result);
        *output_size = 0;
        return NULL;
    }

    int *final_result = realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *output_size = 0;
        return NULL;
    }

    *output_size = count;
    return final_result;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;

    int *odd_numbers = filter_odd(numbers, size, &odd_count);
    if (odd_numbers != NULL && odd_count > 0) {
        printf("Odd numbers: ");
        for (size_t i = 0; i < odd_count; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    } else {
        printf("No odd numbers found or allocation failed.\n");
    }

    return 0;
}