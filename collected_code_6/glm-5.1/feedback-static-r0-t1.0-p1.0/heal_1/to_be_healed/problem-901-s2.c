#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long gcd(long long a, long long b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    long long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long smallest_multiple(int n) {
    if (n < 1) {
        return 0;
    }
    long long result = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'current_gcd' can be reduced. [variableScope]
     */
    long long current_gcd;
    for (int i = 2; i <= n; i++) {
        current_gcd = gcd(result, i);
        if (current_gcd == 0) {
            return 0;
        }
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'LLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'LLONG_MAX'
         */
        if (result > 0 && i / current_gcd > LLONG_MAX / result) {
            return 0;
        }
        result = result / current_gcd * i;
    }
    return result;
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
    n = atoi(argv[1]);
    if (n < 1) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = smallest_multiple(n);
    if (result == 0) {
        fprintf(stderr, "Error: Overflow detected or invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}