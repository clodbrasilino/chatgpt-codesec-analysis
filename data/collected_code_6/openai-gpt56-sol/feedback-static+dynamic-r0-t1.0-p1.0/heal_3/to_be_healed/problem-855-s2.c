#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

static bool has_even_parity(uint64_t value)
{
    bool even = true;

    while (value != UINT64_C(0)) {
        even = !even;
        value &= value - UINT64_C(1);
    }

    return even;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *start = input;

    /* Possible weaknesses found:
     *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
     *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
     */
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_even_parity((uint64_t)parsed) ? "Even parity" : "Odd parity");
    return EXIT_SUCCESS;
}