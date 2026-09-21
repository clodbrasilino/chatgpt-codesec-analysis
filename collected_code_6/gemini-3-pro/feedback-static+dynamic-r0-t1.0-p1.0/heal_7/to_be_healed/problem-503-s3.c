#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    if (length <= 1) {
        *out_length = 0;
        return NULL;
    }

    *out_length = length - 1;
    int* result = (int*)malloc(*out_length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_length; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1579388472 + 888888888 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:4812,execs:2808,op:havoc,rep:8)
         * UBSan: signed integer overflow: -1837658568 + -1196716488 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:7290,execs:4184,op:havoc,rep:7)
         */
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[10000];
    size_t length = 0;

    int num;
    int c;
    while (length < 10000) {
        if (scanf("%d", &num) == 1) {
            list[length++] = num;
        } else {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = getchar();
            if (c == EOF) {
                break;
            }
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    if (result != NULL || out_length > 0) {
        for (size_t i = 0; i < out_length; ++i) {
            printf("%d", result[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        free(result);
    }
    printf("]\n");

    return 0;
}