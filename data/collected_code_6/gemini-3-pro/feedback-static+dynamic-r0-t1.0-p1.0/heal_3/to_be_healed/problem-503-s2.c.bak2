#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  */

int* add_consecutive(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *out_size = 0;
        return malloc(1);
    }

    if (size == 1) {
        *out_size = 1;
        int* res = malloc(sizeof(int));
        if (res != NULL) {
            res[0] = arr[0];
        }
        return res;
    }

    *out_size = size - 1;
    int* result = malloc(*out_size * sizeof(int));
    if (result == NULL) {
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
        int res = scanf("%d", &val);
        if (res == 1) {
            if (size >= capacity) {
                capacity = (capacity == 0) ? 16 : capacity * 2;
                int* temp = realloc(input, capacity * sizeof(int));
                if (!temp) {
                    free(input);
                    return 1;
                }
                input = temp;
            }
            input[size++] = val;
        } else {
            int c = getchar();
            if (c == EOF) {
                break;
            }
        }
    }

    size_t out_size = 0;
    int* result = add_consecutive(input, size, &out_size);
    
    if (result != NULL || (size == 0 && input == NULL)) {
        printf("[");
        for (size_t i = 0; i < out_size; i++) {
            printf("%d", result[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    }

    free(input);
    return 0;
}