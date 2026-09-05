#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long smallest_multiple(int n) {
    if (n < 1) {
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        unsigned long long current_gcd = gcd(result, (unsigned long long)i);
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
        if (result > ULLONG_MAX / ((unsigned long long)i / current_gcd)) {
            return 0;
        }
        result *= (unsigned long long)i / current_gcd;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < 1 || val > 40) {
        return EXIT_FAILURE;
    }
    unsigned long long res = smallest_multiple((int)val);
    if (res == 0) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", res);
    return EXIT_SUCCESS;
}