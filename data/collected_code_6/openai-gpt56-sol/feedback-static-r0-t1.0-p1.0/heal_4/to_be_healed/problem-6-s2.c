#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

static bool parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    const char *cursor;
    uint64_t first;
    uint64_t second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
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

    cursor = input;

    if (!parse_uint64(&cursor, &first) ||
        !parse_uint64(&cursor, &second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(differ_by_one_bit(first, second) ? "Yes" : "No");
    return EXIT_SUCCESS;
}