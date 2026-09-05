#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

const char* check_divisor_count_parity(long long n) {
    if (n <= 0) {
        return "invalid";
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     */
    long long root = (long long)sqrt((double)n);
    if (root * root == n) {
        return "odd";
    }
    return "even";
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Error: Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    const char *result = check_divisor_count_parity(val);
    printf("%s\n", result);

    return EXIT_SUCCESS;
}