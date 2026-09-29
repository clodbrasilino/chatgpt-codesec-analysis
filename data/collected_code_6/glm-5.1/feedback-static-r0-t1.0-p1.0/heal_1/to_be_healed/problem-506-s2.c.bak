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
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
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
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return 0;
}