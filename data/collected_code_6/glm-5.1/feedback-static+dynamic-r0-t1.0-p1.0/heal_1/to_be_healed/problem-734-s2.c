#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long sum_of_products(int *arr, int n) {
    long long total = 0;
    long long current = 0;
    for (int i = 0; i < n; i++) {
        current = current * arr[i] + arr[i];
        total += current;
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <elements>\n", argv[0]);
        return 1;
    }
    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr[i] = atoi(argv[i + 1]);
    }
    long long result = sum_of_products(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}