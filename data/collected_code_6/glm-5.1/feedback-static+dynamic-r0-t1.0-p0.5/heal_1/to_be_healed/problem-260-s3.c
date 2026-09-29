#include <stdio.h>
#include <stdlib.h>

unsigned long long nsw_prime(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 1;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = (2 * b * b) + a;
        a = b;
        b = c;
    }
    return b;
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
    if (n < 1) {
        return EXIT_FAILURE;
    }
    unsigned long long result = nsw_prime(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}