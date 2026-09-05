#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int last_two_digits_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n >= 10) {
        return 0;
    }
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return (int)(result % 100);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please provide a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int res = last_two_digits_factorial(n);
    if (res == -1) {
        fprintf(stderr, "Factorial is not defined for negative numbers.\n");
        return EXIT_FAILURE;
    }
    printf("%02d\n", res);
    return EXIT_SUCCESS;
}