#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if (size == 0 || size == 1) {
        *out_size = 0;
        int* empty = malloc(1);
        if (empty) {
            /* Possible weaknesses found:
             * ASan: heap-buffer-overflow (AFL crash: id:000001,sig:06,src:000002,time:999,execs:226,op:havoc,rep:9)
             * UBSan: store to address 0x6020000000d0 with insufficient space for an object of type 'int' (AFL crash: id:000001,sig:06,src:000002,time:999,execs:226,op:havoc,rep:9)
             */
            *empty = 0;
        }
        return empty;
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:20,execs:17,op:(null),pos:0; likely memory-safety defect
  */

int main(void) {
    int* input = NULL;
    size_t size = 0;
    size_t capacity = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'val' can be reduced. [variableScope]
     *  Variable 'val' is assigned a value that is never used. [unreadVariable]
     */
    int val = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }

    char* token = strtok(buffer, " \n\r\t,[]");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        val = atoi(token);
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
        token = strtok(NULL, " \n\r\t,[]");
    }

    size_t out_size = 0;
    int* result = add_consecutive(input, size, &out_size);
    
    if (result != NULL) {
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