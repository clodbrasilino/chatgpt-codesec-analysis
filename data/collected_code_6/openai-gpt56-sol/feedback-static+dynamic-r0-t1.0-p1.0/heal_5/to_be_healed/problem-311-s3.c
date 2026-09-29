#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 14, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t bit = UINT32_C(1) << 31;

    while (bit != 0U && (value & bit) != 0U) {
        bit >>= 1;
    }

    return value | bit;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[64];
    char *end;
    uintmax_t input;

    if (fgets(line, sizeof line, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_leftmost_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}