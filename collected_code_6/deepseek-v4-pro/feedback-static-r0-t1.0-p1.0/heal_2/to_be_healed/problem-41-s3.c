#include <stdio.h>
#include <stdlib.h>

int filter_even(const int *input, int input_size, int **output, int *output_size) {
    if (input == NULL || output == NULL || output_size == NULL || input_size < 0) {
        return -1;
    }
    
    *output_size = 0;
    for (int i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            (*output_size)++;
        }
    }
    
    *output = (int *)malloc((*output_size) * sizeof(int));
    if (*output == NULL && *output_size > 0) {
        return -1;
    }
    
    int j = 0;
    for (int i = 0; i < input_size; i++) {
        if (input[i] % 2 == 0) {
            (*output)[j++] = input[i];
        }
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'numbers' can be declared as const array [constVariable]
     */
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *even_numbers = NULL;
    int even_count = 0;
    
    if (filter_even(numbers, 10, &even_numbers, &even_count) == 0) {
        for (int i = 0; i < even_count; i++) {
            printf("%d ", even_numbers[i]);
        }
        printf("\n");
        free(even_numbers);
    }
    
    return 0;
}