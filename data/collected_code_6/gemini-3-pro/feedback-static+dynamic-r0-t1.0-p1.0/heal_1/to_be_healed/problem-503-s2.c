#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
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
        result[i] = arr[i] + arr[i + 1];
    }

    return result;
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(input) / sizeof(input[0]);
    size_t out_size = 0;

    int* result = add_consecutive(input, size, &out_size);
    
    if (result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}