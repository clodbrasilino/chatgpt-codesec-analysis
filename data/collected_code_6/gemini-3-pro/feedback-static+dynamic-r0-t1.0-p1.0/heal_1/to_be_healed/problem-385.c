#include <stdio.h>
#include <stdlib.h>

unsigned long long perrin(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);

    if (n < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (n > 50) {
        fprintf(stderr, "Error: n is too large, it may cause performance issues or integer overflow.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = perrin(n);
    printf("The %d'th Perrin number is %llu\n", n, result);

    return EXIT_SUCCESS;
}