#include <stdio.h>
#include <stdlib.h>

int* filter_odd_numbers(const int* input, size_t input_size, size_t* output_size) {
    if (input == NULL || output_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            count++;
        }
    }

    if (count == 0) {
        *output_size = 0;
        return NULL;
    }

    int* output = (int*)malloc(count * sizeof(int));
    if (output == NULL) {
        *output_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            output[index++] = input[i];
        }
    }

    *output_size = count;
    return output;
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t input_size = sizeof(input) / sizeof(input[0]);
    size_t output_size = 0;

    int* odd_numbers = filter_odd_numbers(input, input_size, &output_size);

    if (odd_numbers != NULL) {
        for (size_t i = 0; i < output_size; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    }

    return 0;
}