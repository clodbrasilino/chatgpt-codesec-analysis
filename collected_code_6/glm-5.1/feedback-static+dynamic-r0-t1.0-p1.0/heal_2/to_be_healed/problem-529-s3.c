#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 31, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 17, got <no output>
  */

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    long long a = 2;
    long long b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        return EXIT_FAILURE;
    }
    long long result = jacobsthal_lucas(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}