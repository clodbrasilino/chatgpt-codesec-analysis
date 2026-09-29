#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  */

int* filter_odd_numbers(const int* array, size_t size, size_t* out_size) {
    if (array == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 != 0) {
            count++;
        }
    }

    *out_size = count;

    if (count == 0) {
        return NULL;
    }

    int* odd_array = (int*)malloc(count * sizeof(int));
    if (odd_array == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 != 0) {
            odd_array[index++] = array[i];
        }
    }

    return odd_array;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t out_size = 0;

    int* odd_numbers = filter_odd_numbers(numbers, size, &out_size);

    if (odd_numbers != NULL || out_size == 0) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}