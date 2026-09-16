#include <stdio.h>
#include <stdlib.h>

int* find_divisible_numbers(const int* arr, size_t size, int m, int n, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }
    
    if (m == 0 && n == 0) {
        *out_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    *out_size = 0;
    for (size_t i = 0; i < size; i++) {
        int is_divisible = 0;
        if (m != 0 && arr[i] % m == 0) {
            is_divisible = 1;
        }
        if (n != 0 && arr[i] % n == 0) {
            is_divisible = 1;
        }
        
        if (is_divisible) {
            result[*out_size] = arr[i];
            (*out_size)++;
        }
    }

    if (*out_size == 0) {
        free(result);
        return NULL;
    }

    int* resized_result = (int*)realloc(result, (*out_size) * sizeof(int));
    if (resized_result == NULL) {
        return result; 
    }

    return resized_result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    size_t out_size = 0;

    int* divisible_numbers = find_divisible_numbers(numbers, size, m, n, &out_size);

    if (divisible_numbers != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", divisible_numbers[i]);
        }
        printf("\n");
        free(divisible_numbers);
    } else {
        printf("\n");
    }

    return 0;
}