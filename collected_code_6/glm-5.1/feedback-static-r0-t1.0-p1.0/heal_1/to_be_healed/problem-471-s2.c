#include <stdio.h>
#include <stdlib.h>

unsigned long long find_remainder(int *arr, size_t size, int n) {
    unsigned long long result = 1 % n;
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            fprintf(stderr, "Error\n");
            exit(EXIT_FAILURE);
        }
        result = (result * (unsigned long long)arr[i]) % n;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    size_t size = (size_t)argc - 2;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    size_t i;
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr[i] = atoi(argv[i + 2]);
    }
    printf("%llu\n", find_remainder(arr, size, n));
    free(arr);
    return EXIT_SUCCESS;
}