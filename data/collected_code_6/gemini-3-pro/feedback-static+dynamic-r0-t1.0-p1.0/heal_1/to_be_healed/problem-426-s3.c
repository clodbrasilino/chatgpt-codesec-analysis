#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  */

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
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t out_length = 0;

    int* odd_numbers = filter_odd_numbers(numbers, length, &out_length);

    if (odd_numbers != NULL) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d ", odd_numbers[i]);
        }
        printf("\n");
        free(odd_numbers);
    } else if (out_length == 0) {
        printf("\n");
    }

    return 0;
}