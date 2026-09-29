#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t square;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    square = n * n;
    *result = square * (UINT64_C(2) * square - UINT64_C(1));
    return 1;
}

static void discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start) && *start != '\n') {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    if (*start == '+') {
        ++start;
    }

    if (!isdigit((unsigned char)*start)) {
        return 0;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     */
    errno = 0;
    parsed = strtoumax(start, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     */
    if (errno == ERANGE || parsed > UINT64_MAX || end == start) {
        return 0;
    }

    while (*end != '\0' && *end != '\n') {
        if (!isspace((unsigned char)*end)) {
            return 0;
        }
        ++end;
    }

    if (*end == '\0') {
        size_t length = (size_t)(end - buffer);

        if (length == sizeof buffer - 1 && buffer[length - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                discard_line();
                return 0;
            }
            if (ch == EOF && ferror(stdin)) {
                return 0;
            }
        }
    }

    if (ferror(stdin)) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}