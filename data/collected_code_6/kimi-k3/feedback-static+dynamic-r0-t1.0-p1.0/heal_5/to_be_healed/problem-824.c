#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [5, 7], got <no output>
  *  test case 0 failed: expected [1, 3, 5], got <no output>
  *  test case 2 failed: expected [1, 3], got <no output>
  */

int* remove_even(const int* arr, size_t size, size_t* new_size) {
    if (arr == NULL || new_size == NULL) {
        return NULL;
    }
    
    int* result = malloc(size * sizeof(int));
    if (result == NULL && size > 0) {
        return NULL;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            result[count++] = arr[i];
        }
    }
    
    *new_size = count;
    return result;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t new_size = 0;
    
    int* odd_numbers = remove_even(numbers, size, &new_size);
    if (odd_numbers == NULL) {
        return EXIT_FAILURE;
    }
    
    printf("[");
    for (size_t i = 0; i < new_size; i++) {
        printf("%d", odd_numbers[i]);
        if (i < new_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    free(odd_numbers);
    return EXIT_SUCCESS;
}