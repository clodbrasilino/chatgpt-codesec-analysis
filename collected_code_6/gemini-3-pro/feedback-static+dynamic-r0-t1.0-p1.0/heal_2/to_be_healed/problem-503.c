#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
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
        int* result = (int*)malloc(sizeof(int));
        if (result == NULL) {
            *out_length = 0;
            return NULL;
        }
        result[0] = list[0];
        *out_length = 1;
        return result;
    }

    *out_length = length - 1;
    int* result = (int*)malloc((*out_length) * sizeof(int));
    if (result == NULL) {
        *out_length = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_length; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1111111111 + 1111111111 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000007,time:6261,execs:3133,op:havoc,rep:7)
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
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int num;
    while (scanf("%d", &num) == 1) {
        if (length == capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(list, capacity * sizeof(int));
            if (temp == NULL) {
                free(list);
                fprintf(stderr, "Memory allocation failed\n");
                return EXIT_FAILURE;
            }
            list = temp;
        }
        list[length++] = num;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'length==0' is not redundant
     */
    if (length == 0) {
        free(list);
        return EXIT_SUCCESS;
    }

    size_t out_length = 0;
    int* result = add_consecutive_numbers(list, length, &out_length);

    if (result != NULL) {
        printf("[");
        for (size_t i = 0; i < out_length; i++) {
            printf("%d", result[i]);
            if (i < out_length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    /* Possible weaknesses found:
     *  Condition 'length>0' is always true
     *  Condition 'length>0' is always true [knownConditionTrueFalse]
     */
    } else if (out_length == 0 && length > 0) {
        fprintf(stderr, "Memory allocation failed\n");
    }

    free(list);
    return EXIT_SUCCESS;
}