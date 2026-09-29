#include <stdio.h>
#include <stdlib.h>

void find_multiples(int n, int m) {
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", n * i);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int m = atoi(argv[2]);

    if (n <= 0 || m <= 0) {
        fprintf(stderr, "Both n and m must be positive integers.\n");
        return EXIT_FAILURE;
    }

    find_multiples(n, m);

    return EXIT_SUCCESS;
}