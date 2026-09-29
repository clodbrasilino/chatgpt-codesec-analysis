#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int first_factorial_digit(unsigned long long n)
{
    if (n < 2ULL) {
        return 1;
    }

    long double logarithm =
        lgammal((long double)n + 1.0L) / logl(10.0L);

    if (!isfinite(logarithm)) {
        return -1;
    }

    long double fractional_part = logarithm - floorl(logarithm);
    long double leading = powl(10.0L, fractional_part);
    int digit = (int)floorl(leading + 1e-15L);

    if (digit < 1) {
        return 1;
    }

    return digit > 9 ? 9 : digit;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    char *cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    int digit = first_factorial_digit(n);

    if (digit < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}