#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long sum_xor_pairs(int arr[], int n) {
    long long sum = 0;
    int i, j;
    for (i = 0; i < 32; i++) {
        long long ones = 0;
        for (j = 0; j < n; j++) {
            /* Possible weaknesses found:
             * UBSan: left shift of 1 by 31 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:29,execs:29,op:havoc,rep:7)
             */
            if (arr[j] & (1 << i)) {
                ones++;
            }
        }
        long long zeros = n - ones;
        sum += (ones * zeros) * (1LL << i);
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000004,time:1567,execs:805,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    printf("%lld\n", sum_xor_pairs(arr, n));
    free(arr);
    return EXIT_SUCCESS;
}