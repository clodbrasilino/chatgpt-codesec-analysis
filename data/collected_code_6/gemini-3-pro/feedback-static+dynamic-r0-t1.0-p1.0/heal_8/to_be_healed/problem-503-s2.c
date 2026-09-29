#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive(const int* arr, size_t size, size_t* out_size) {
    if (out_size == NULL) {
        return NULL;
    }
    if (arr == NULL && size > 0) {
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000000,time:3432,execs:2589,op:havoc,rep:15; likely memory-safety defect
  */

int main(void) {
    int* input = NULL;
    size_t size = 0;
    size_t capacity = 0;
    int val = 0;

    int c;
    int sign = 1;
    int in_num = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF) {
        if (c == '-' && !in_num) {
            sign = -1;
        } else if (isdigit(c)) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 666666666 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:885,execs:702,op:havoc,rep:3)
             * UBSan: signed integer overflow: 999999999 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:658,execs:525,op:havoc,rep:5)
             * UBSan: signed integer overflow: 555555555 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:396,execs:330,op:havoc,rep:13)
             * UBSan: signed integer overflow: 888888888 * 10 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000023,time:19546,execs:14044,op:havoc,rep:5)
             */
            val = val * 10 + (c - '0');
            in_num = 1;
        } else {
            if (in_num) {
                if (size >= capacity) {
                    capacity = (capacity == 0) ? 16 : capacity * 2;
                    int* temp = realloc(input, capacity * sizeof(int));
                    if (!temp) {
                        free(input);
                        return 1;
                    }
                    input = temp;
                }
                input[size++] = val * sign;
                in_num = 0;
                val = 0;
                sign = 1;
            } else if (c == '-') {
                sign = -1;
            } else {
                sign = 1;
            }
        }
    }
    if (in_num) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 16 : capacity * 2;
            int* temp = realloc(input, capacity * sizeof(int));
            if (!temp) {
                free(input);
                return 1;
            }
            input = temp;
        }
        input[size++] = val * sign;
    }

    size_t out_size = 0;
    int* result = add_consecutive(input, size, &out_size);
    
    if (result != NULL || size == 0) {
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