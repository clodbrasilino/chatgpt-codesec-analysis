#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        if (out_length) *out_length = 0;
        return NULL;
    }

    if (length <= 1) {
        *out_length = 0;
        return NULL;
    }

    *out_length = length - 1;
    int* result = (int*)malloc((*out_length) * sizeof(int));
    if (result == NULL) {
        *out_length = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_length; i++) {
        result[i] = (int)((unsigned int)list[i] + (unsigned int)list[i + 1]);
    }

    return result;
}

int main(void) {
    size_t capacity = 16;
    size_t length = 0;
    int* list = (int*)malloc(capacity * sizeof(int));
    
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    int ch;
    int num = 0;
    int sign = 1;
    int in_num = 0;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch >= '0' && ch <= '9') {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 444444444 * 10 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000027,time:33411,execs:17811,op:havoc,rep:6)
             * UBSan: signed integer overflow: 666000000 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:930,execs:525,op:havoc,rep:8)
             * UBSan: signed integer overflow: 777777777 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:3306,execs:1860,op:havoc,rep:2)
             * UBSan: signed integer overflow: 555555555 * 10 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000022,time:24544,execs:13253,op:havoc,rep:2)
             * UBSan: signed integer overflow: 1111111111 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:1741,execs:975,op:havoc,rep:7)
             */
            num = num * 10 + (ch - '0');
            in_num = 1;
        } else if (ch == '-' && !in_num) {
            sign = -1;
        } else {
            if (in_num) {
                if (length == capacity) {
                    capacity *= 2;
                    int* temp = (int*)realloc(list, capacity * sizeof(int));
                    if (temp == NULL) {
                        free(list);
                        return EXIT_FAILURE;
                    }
                    list = temp;
                }
                list[length++] = num * sign;
                num = 0;
                sign = 1;
                in_num = 0;
            } else if (ch != '-') {
                sign = 1; 
            }
        }
    }
    if (in_num) {
        if (length == capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(list, capacity * sizeof(int));
            if (temp != NULL) {
                list = temp;
            }
        }
        if (list != NULL) {
            list[length++] = num * sign;
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    if (result != NULL && out_length > 0) {
        printf("[");
        for (size_t i = 0; i < out_length; i++) {
            printf("%d", result[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    } else {
        printf("[]\n");
    }

    free(list);
    return EXIT_SUCCESS;
}