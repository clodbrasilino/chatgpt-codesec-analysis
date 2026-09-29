#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

static bool is_woodall(uint64_t number)
{
    uint64_t power_of_two = 2;

    for (uint64_t n = 1; n <= 63; ++n) {
        if (n <= UINT64_MAX / power_of_two &&
            n * power_of_two - 1 == number) {
            return true;
        }

        if (power_of_two > UINT64_MAX / 2) {
            break;
        }

        power_of_two *= 2;
    }

    return false;
}

int main(void)
{
    uintmax_t value;
    int trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &value) != 1 || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing != EOF && isspace((unsigned char)trailing));

    if (trailing != EOF) {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_woodall((uint64_t)value) ? "True" : "False");
    return EXIT_SUCCESS;
}