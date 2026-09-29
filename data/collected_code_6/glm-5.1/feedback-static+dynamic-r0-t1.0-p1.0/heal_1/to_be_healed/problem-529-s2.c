#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 22
  *  test case 0 failed: expected 31, got 42
  *  test case 1 failed: expected 5, got 6
  */

unsigned long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 2;
    }
    unsigned long long a = 2;
    unsigned long long b = 2;
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    unsigned long long c;
    for (int i = 2; i <= n; i++) {
        c = b + 2 * a;
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
    if (n < 0) {
        return EXIT_FAILURE;
    }
    unsigned long long result = jacobsthal_lucas(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}