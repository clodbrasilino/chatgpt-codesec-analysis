#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned int gcd(unsigned int a, unsigned int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned int a;
    unsigned int b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive_integer_a> <positive_integer_b>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a;
    char *endptr_b;
    unsigned long val_a = strtoul(argv[1], &endptr_a, 10);
    unsigned long val_b = strtoul(argv[2], &endptr_b, 10);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (*endptr_a != '\0' || *endptr_b != '\0' || val_a == 0 || val_b == 0 || val_a > UINT_MAX || val_b > UINT_MAX) {
        fprintf(stderr, "Error: Both arguments must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }

    a = (unsigned int)val_a;
    b = (unsigned int)val_b;

    unsigned int result = gcd(a, b);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}