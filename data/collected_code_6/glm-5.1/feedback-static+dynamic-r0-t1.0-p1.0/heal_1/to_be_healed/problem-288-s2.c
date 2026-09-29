#include <stdio.h>
#include <stdlib.h>

int modular_inverse(int a, int p) {
    if (a <= 0 || p <= 1) {
        return 0;
    }
    int result = 1;
    int base = a % p;
    int exponent = p - 2;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % p;
        }
        exponent /= 2;
        base = (base * base) % p;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_elements_with_self_inverse(int *arr, int n, int p) {
    if (arr == NULL || n < 0 || p <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            int inv = modular_inverse(arr[i], p);
            int val = arr[i] % p;
            if (inv == val) {
                count++;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int p = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[2]);
    if (n <= 0 || n + 3 > argc) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr[i] = atoi(argv[3 + i]);
    }
    int result = count_elements_with_self_inverse(arr, n, p);
    printf("%d\n", result);
    free(arr);
    return 0;
}