#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

int* add_consecutive_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    if (length == 0) {
        *out_length = 0;
        return NULL;
    }

    if (length == 1) {
        *out_length = 1;
        int* result = (int*)malloc(sizeof(int));
        if (result != NULL) {
            result[0] = list[0];
        }
        return result;
    }

    *out_length = length - 1;
    int* result = (int*)malloc(*out_length * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_length; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 293717788 + 2062812956 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:45030,execs:21759,op:havoc,rep:3)
         * UBSan: signed integer overflow: 2062812956 + 2062812956 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:5065,execs:2470,op:havoc,rep:11)
         */
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[10000];
    size_t length = 0;

    while (length < 10000) {
        if (scanf("%d", &list[length]) == 1) {
            length++;
        } else {
            if (getchar() == EOF) {
                break;
            }
        }
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    printf("[");
    if (result != NULL) {
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