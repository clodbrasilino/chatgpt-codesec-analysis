#include <stdio.h>
#include <stdlib.h>

int perrin(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    } else if (n == 1) {
        return 3;
    } else if (n == 2) {
        return 0;
    } else if (n == 3) {
        return 2;
    } else {
        return perrin(n - 2) + perrin(n - 3);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", perrin(n));
    return EXIT_SUCCESS;
}