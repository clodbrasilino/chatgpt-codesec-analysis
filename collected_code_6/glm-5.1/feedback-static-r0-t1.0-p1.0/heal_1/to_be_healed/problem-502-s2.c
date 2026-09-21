#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int a = 10;
    int b = 3;
    
    if (argc == 3) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        a = atoi(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        b = atoi(argv[2]);
    }
    
    int result = find_remainder(a, b);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}