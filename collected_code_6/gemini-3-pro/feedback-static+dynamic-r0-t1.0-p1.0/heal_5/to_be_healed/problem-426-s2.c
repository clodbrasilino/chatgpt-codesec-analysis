#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int* filter_odd_numbers(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    int* odd_arr = (int*)malloc(count * sizeof(int));
    if (odd_arr == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            odd_arr[index++] = arr[i];
        }
    }

    *out_size = count;
    return odd_arr;
}

int main(void) {
    int arr[10000];
    size_t size = 0;
    int c;
    int val = 0;
    int sign = 1;
    int has_val = 0;

    while ((c = getchar()) != EOF) {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 777777777 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:8501,execs:753,op:havoc,rep:7)
             * UBSan: signed integer overflow: 888888888 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:5543,execs:529,op:havoc,rep:6)
             * UBSan: signed integer overflow: 555555555 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:385,execs:63,op:havoc,rep:8)
             */
            val = val * 10 + (c - '0');
            has_val = 1;
        } else {
            if (has_val) {
                arr[size++] = val * sign;
                has_val = 0;
                val = 0;
            }
            sign = 1;
        }
    }
    if (has_val) {
        arr[size++] = val * sign;
    }

    size_t out_size = 0;
    int* odd_arr = filter_odd_numbers(arr, size, &out_size);

    printf("[");
    if (odd_arr != NULL && out_size > 0) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d", odd_arr[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        free(odd_arr);
    }
    printf("]\n");

    return EXIT_SUCCESS;
}