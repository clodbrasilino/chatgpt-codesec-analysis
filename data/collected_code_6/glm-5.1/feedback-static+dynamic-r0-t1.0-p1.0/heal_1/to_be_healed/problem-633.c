#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
unsigned long long sum_of_xor_pairs(int *arr, size_t n) {
    unsigned long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            sum += (unsigned long long)(arr[i] ^ arr[j]);
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    size_t n = (size_t)(argc - 1);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr[i] = atoi(argv[i + 1]);
    }
    unsigned long long result = sum_of_xor_pairs(arr, n);
    printf("%llu\n", result);
    free(arr);
    return 0;
}