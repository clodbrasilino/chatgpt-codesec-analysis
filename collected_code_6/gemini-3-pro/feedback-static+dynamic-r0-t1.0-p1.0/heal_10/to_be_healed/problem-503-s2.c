#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  */

int* add_consecutive(const int* arr, size_t size, size_t* out_size) {
    if (out_size == NULL) {
        return NULL;
    }
    if (arr == NULL || size < 2) {
        *out_size = 0;
        return NULL;
    }
    *out_size = size - 1;
    int* result = malloc(*out_size * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }
    for (size_t i = 0; i < *out_size; i++) {
        result[i] = (int)((unsigned int)arr[i] + (unsigned int)arr[i + 1]);
    }
    return result;
}

int main(void) {
    int* input = NULL;
    size_t size = 0;
    size_t capacity = 0;
    int val;

    while (1) {
        if (scanf("%d", &val) == 1) {
            if (size >= capacity) {
                size_t new_capacity = (capacity == 0) ? 16 : capacity * 2;
                int* temp = realloc(input, new_capacity * sizeof(int));
                if (!temp) {
                    free(input);
                    return 1;
                }
                input = temp;
                capacity = new_capacity;
            }
            input[size++] = val;
        } else {
            int c = getchar();
            if (c == EOF || c == '\n') {
                break;
            }
        }
    }

    size_t out_size = 0;
    int* result = add_consecutive(input, size, &out_size);
    
    printf("[");
    for (size_t i = 0; i < out_size; i++) {
        printf("%d", result[i]);
        if (i < out_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(result);
    free(input);
    
    return 0;
}