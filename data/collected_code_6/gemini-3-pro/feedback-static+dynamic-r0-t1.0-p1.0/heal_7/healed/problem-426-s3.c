#include <stdio.h>
#include <stdlib.h>

int* filter_odd_numbers(const int* array, size_t length, size_t* out_length) {
    if (array == NULL || out_length == NULL) {
        return NULL;
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < length; i++) {
        if (array[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0) {
        *out_length = 0;
        return NULL;
    }

    int* odd_array = (int*)malloc(odd_count * sizeof(int));
    if (odd_array == NULL) {
        *out_length = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < length; i++) {
        if (array[i] % 2 != 0) {
            odd_array[index++] = array[i];
        }
    }

    *out_length = odd_count;
    return odd_array;
}

int main(void) {
    int* numbers = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int num;
    int res;

    while ((res = scanf("%d", &num)) != EOF) {
        if (res == 1) {
            if (length >= capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                int* temp = (int*)realloc(numbers, new_capacity * sizeof(int));
                if (!temp) {
                    free(numbers);
                    return 1;
                }
                numbers = temp;
                capacity = new_capacity;
            }
            numbers[length++] = num;
        } else {
            fgetc(stdin);
        }
    }

    size_t out_length = 0;
    int* odd_numbers = NULL;
    
    if (length > 0) {
        odd_numbers = filter_odd_numbers(numbers, length, &out_length);
    }

    printf("[");
    if (odd_numbers != NULL && out_length > 0) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d", odd_numbers[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        free(odd_numbers);
    }
    printf("]\n");

    free(numbers);
    return 0;
}