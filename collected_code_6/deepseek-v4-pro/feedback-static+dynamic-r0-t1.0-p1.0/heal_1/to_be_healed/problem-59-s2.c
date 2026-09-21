#include <stdio.h>
#include <stdlib.h>

long long octagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (3 * n - 2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    long long result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return 1;
    }

    result = octagonal_number(n);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}