#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 2 failed: expected 15, got 2147483663
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
    uintmax_t input;
    int result;
    int ch;

    errno = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    result = scanf("%" SCNuMAX, &input);

    if (result != 1 || errno == ERANGE || input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r' ||
             ch == '\n' || ch == '\v' || ch == '\f');

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_leftmost_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}