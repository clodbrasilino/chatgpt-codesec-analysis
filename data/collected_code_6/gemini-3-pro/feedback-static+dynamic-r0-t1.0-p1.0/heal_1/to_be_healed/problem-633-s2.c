#include <stdio.h>
#include <stdlib.h>

long long int sumOfXorPairs(const int* arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    long long int sum = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<32' is not redundant
     */
    for (int i = 0; i < 32; i++) {
        long long int zeroCount = 0;
        long long int oneCount = 0;

        for (size_t j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Signed integer overflow for expression '1<<i'. [integerOverflow]
             * UBSan: left shift of 1 by 31 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:18,execs:13,op:havoc,rep:5)
             *  Integer overflow
             *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
             *  Shift
             */
            if (arr[j] & (1 << i)) {
                oneCount++;
            } else {
                zeroCount++;
            }
        }
        sum += (zeroCount * oneCount) * (1LL << i);
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000000,time:26,execs:16,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int* arr = NULL;
    size_t n = 0;
    int temp = 0;
    size_t capacity = 10;

    arr = (int*)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    while (scanf("%d", &temp) == 1) {
        if (n >= capacity) {
            size_t new_capacity = capacity * 2;
            int* temp_arr = (int*)realloc(arr, new_capacity * sizeof(int));
            if (temp_arr == NULL) {
                free(arr);
                return 1;
            }
            arr = temp_arr;
            capacity = new_capacity;
        }
        arr[n++] = temp;
    }

    if (n > 0) {
        long long int result = sumOfXorPairs(arr, n);
        printf("%lld\n", result);
    }

    free(arr);
    return 0;
}