#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long sum_xor_pairs(const int arr[], int n) {
    long long sum = 0;
    int i, j;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<32' is not redundant
     */
    for (i = 0; i < 32; i++) {
        long long ones = 0;
        /* Possible weaknesses found:
         *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
         *  Signed integer overflow for expression '1<<i'. [integerOverflow]
         *  Integer overflow
         *  Shift
         */
        int32_t mask = 1 << i;
        for (j = 0; j < n; j++) {
            if (arr[j] & mask) {
                ones++;
            }
        }
        long long zeros = n - ones;
        sum += (ones * zeros) * (1LL << i);
    }
    return sum;
}

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