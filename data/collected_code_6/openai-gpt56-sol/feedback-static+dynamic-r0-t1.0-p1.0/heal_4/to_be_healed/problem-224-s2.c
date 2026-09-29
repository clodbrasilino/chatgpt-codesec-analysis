#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  */

static unsigned int count_set_bits(uint64_t value)
{
    unsigned int count = 0;

    while (value != UINT64_C(0)) {
        value &= value - UINT64_C(1);
        ++count;
    }

    return count;
}

int main(void)
{
    uintmax_t parsed_value;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && isspace((unsigned char)ch)) {
    }

    if (ch == EOF || ch == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (ungetc(ch, stdin) == EOF) {
        return EXIT_FAILURE;
    }

    errno = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &parsed_value) != 1 ||
        errno == ERANGE ||
        parsed_value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_set_bits((uint64_t)parsed_value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}