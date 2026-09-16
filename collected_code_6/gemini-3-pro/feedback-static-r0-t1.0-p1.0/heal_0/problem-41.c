#include <stdio.h>
#include <stdlib.h>

int* filter_even(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }

    *out_size = count;
    if (count == 0) {
        return NULL;
    }

    int* even_arr = (int*)malloc(count * sizeof(int));
    if (even_arr == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            even_arr[j++] = arr[i];
        }
    }

    return even_arr;
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(input) / sizeof(input[0]);
    size_t out_size = 0;

    int* even_numbers = filter_even(input, size, &out_size);

    if (even_numbers != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", even_numbers[i]);
        }
        printf("\n");
        free(even_numbers);
    } else if (out_size == 0) {
        printf("\n");
    }

    return 0;
}