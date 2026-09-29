#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != UINTMAX_C(0)) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[sizeof buffer - 2] != '\n') {
        size_t length = 0;
        /* Possible weaknesses found:
         *  The scope of the variable 'ch' can be reduced. [variableScope]
         */
        int ch;

        while (buffer[length] != '\0') {
            ++length;
        }

        if (length == sizeof buffer - 1) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return 0;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    errno = 0;
    parsed = strtoimax(start, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     */
    if (start == end || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (!read_intmax(&first) || !read_intmax(&second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n",
               gcd(magnitude(first), magnitude(second))) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}