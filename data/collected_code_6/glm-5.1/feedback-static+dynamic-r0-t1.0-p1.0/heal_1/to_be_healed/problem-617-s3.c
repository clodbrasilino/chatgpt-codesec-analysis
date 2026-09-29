#include <stdio.h>
#include <stdlib.h>

int min_jumps(int d, int jmp) {
    if (jmp < 0) {
        jmp = -jmp;
    }
    if (jmp == 0) {
        if (d == 0) {
            return 0;
        } else {
            return -1;
        }
    }
    int steps = d / jmp;
    if (d % jmp == 0) {
        return steps;
    } else {
        return steps + 1 + 1;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int d = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int jmp = atoi(argv[2]);
    int res = min_jumps(d, jmp);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}