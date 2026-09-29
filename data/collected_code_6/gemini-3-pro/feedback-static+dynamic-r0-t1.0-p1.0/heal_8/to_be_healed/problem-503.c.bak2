#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

    if (length < 2) {
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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1468588942 + 747385742 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000017,time:55899,execs:21867,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1228654364 + 1228654364 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:30182,execs:11421,op:havoc,rep:14)
         * UBSan: signed integer overflow: -1305424328 + -1196716488 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2376,execs:645,op:havoc,rep:11)
         */
        result[i] = list[i] + list[i + 1];
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

    int num;
    while (!feof(stdin)) {
        if (scanf("%d", &num) == 1) {
            if (length == capacity) {
                capacity *= 2;
                int* temp = (int*)realloc(list, capacity * sizeof(int));
                if (temp == NULL) {
                    free(list);
                    return EXIT_FAILURE;
                }
                list = temp;
            }
            list[length++] = num;
        } else {
            if (getchar() == EOF) {
                break;
            }
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    for (size_t i = 0; i < out_length; i++) {
        printf("%d", result[i]);
        if (i < out_length - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    if (result != NULL) {
        free(result);
    }
    free(list);
    return EXIT_SUCCESS;
}