#include <stdio.h>
#include <stdlib.h>

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
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    long long c;
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
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    if (n < 0) {
        return EXIT_FAILURE;
    }
    long long result = jacobsthal_lucas(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}