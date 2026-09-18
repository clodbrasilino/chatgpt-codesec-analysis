#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
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
    int* numbers = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if ((ch >= '0' && ch <= '9') || (ch == '-')) {
            ungetc(ch, stdin);
            int num;
            if (scanf("%d", &num) == 1) {
                if (length >= capacity) {
                    capacity = capacity == 0 ? 16 : capacity * 2;
                    int* temp = realloc(numbers, capacity * sizeof(int));
                    if (!temp) {
                        free(numbers);
                        return 1;
                    }
                    numbers = temp;
                }
                numbers[length++] = num;
            }
        }
    }

    size_t out_length = 0;
    int* odd_numbers = filter_odd_numbers(numbers, length, &out_length);

    printf("[");
    if (odd_numbers != NULL) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d%s", odd_numbers[i], i < out_length - 1 ? ", " : "");
        }
        free(odd_numbers);
    }
    printf("]\n");

    free(numbers);
    return 0;
}