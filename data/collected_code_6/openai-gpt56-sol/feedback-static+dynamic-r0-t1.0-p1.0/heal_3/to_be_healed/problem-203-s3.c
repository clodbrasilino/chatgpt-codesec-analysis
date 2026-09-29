#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  */

static unsigned int hamming_distance(uint32_t first, uint32_t second)
{
    uint32_t difference = first ^ second;
    unsigned int distance = 0U;

    while (difference != UINT32_C(0)) {
        difference &= difference - UINT32_C(1);
        ++distance;
    }

    return distance;
}

static int parse_uint32(const char **input, uint32_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    uint32_t first;
    uint32_t second;
    int trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32 " %" SCNu32, &first, &second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing != '\n' && trailing != EOF &&
             (trailing == ' ' || trailing == '\t' ||
              trailing == '\r' || trailing == '\f' ||
              trailing == '\v'));

    if (trailing != '\n' && trailing != EOF) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", hamming_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}