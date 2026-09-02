#include <stdio.h>
#include <stdlib.h>

int* filter_even_numbers(const int* input_array, int input_size, int* output_size) {
    if (output_size == NULL) {
        return NULL;
    }
    *output_size = 0;

    if (input_array == NULL || input_size <= 0) {
        return NULL;
    }

    int* even_numbers = (int*)malloc(input_size * sizeof(int));
    if (even_numbers == NULL) {
        return NULL;
    }

    int even_count = 0;
    for (int i = 0; i < input_size; i++) {
        if (input_array[i] % 2 == 0) {
            even_numbers[even_count] = input_array[i];
            even_count++;
        }
    }

    if (even_count == 0) {
        free(even_numbers);
        return NULL;
    }

    int* resized_array = (int*)realloc(even_numbers, even_count * sizeof(int));
    if (resized_array == NULL) {
        free(even_numbers);
        return NULL;
    }

    *output_size = even_count;
    return resized_array;
}

int main(void) {
    int test_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int test_size = sizeof(test_array) / sizeof(test_array[0]);
    int result_size = 0;

    int* even_numbers = filter_even_numbers(test_array, test_size, &result_size);

    if (even_numbers != NULL && result_size > 0) {
        printf("Even numbers: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", even_numbers[i]);
        }
        printf("\n");
        free(even_numbers);
    } else {
        printf("No even numbers found or error occurred\n");
    }

    return 0;
}