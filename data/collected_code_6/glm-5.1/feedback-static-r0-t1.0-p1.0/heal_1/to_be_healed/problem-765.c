#include <stdio.h>
#include <stdlib.h>

int nth_polite_number(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    int bit_count = 0;
    int temp = n;
    while (temp > 0) {
        if (temp & 1) {
            bit_count++;
        }
        temp >>= 1;
    }
    return n + bit_count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    int result = nth_polite_number(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}