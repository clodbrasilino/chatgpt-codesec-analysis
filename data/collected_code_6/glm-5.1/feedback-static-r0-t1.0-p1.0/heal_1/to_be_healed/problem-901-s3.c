#include <stdio.h>
#include <stdlib.h>

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
     *  The scope of the variable 'common_divisor' can be reduced. [variableScope]
     */
    long long common_divisor;
    for (int i = 2; i <= n; i++) {
        common_divisor = gcd(result, i);
        /* Possible weaknesses found:
         *  '__LLONG_MAX__' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier '__LLONG_MAX__'
         */
        if (result > __LLONG_MAX__ / (i / common_divisor)) {
            return -1;
        }
        result = result * (i / common_divisor);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 1 || val > 40) {
        fprintf(stderr, "Error: n must be an integer between 1 and 40\n");
        return EXIT_FAILURE;
    }
    long long res = smallest_multiple((int)val);
    if (res == -1) {
        fprintf(stderr, "Error: Integer overflow detected\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res);
    return EXIT_SUCCESS;
}