#include <stdio.h>
#include <stdlib.h>

int count_odd_set_bits(const int *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        int num = arr[i];
        int set_bits = 0;
        while (num) {
            set_bits ^= 1;
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:3320,execs:2290,op:havoc,rep:2)
             */
            num &= (num - 1);
        }
        if (set_bits) {
            count++;
        }
    }
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000006,time:6992,execs:4826,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int size;
    if (scanf("%d", &size) != 1 || size <= 0) {
        return 1;
    }

    int *arr = malloc((size_t)size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    int result = count_odd_set_bits(arr, size);
    printf("%d\n", result);

    free(arr);
    return 0;
}