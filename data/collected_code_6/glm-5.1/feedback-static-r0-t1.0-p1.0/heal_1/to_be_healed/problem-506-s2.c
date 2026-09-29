#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long permutation(int n, int k) {
    unsigned long long result = 1;
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'ULLONG_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
        if (result > ULLONG_MAX / (n - i)) {
            return 0;
        }
        result *= (n - i);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n, k;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    k = atoi(argv[2]);
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return 0;
}