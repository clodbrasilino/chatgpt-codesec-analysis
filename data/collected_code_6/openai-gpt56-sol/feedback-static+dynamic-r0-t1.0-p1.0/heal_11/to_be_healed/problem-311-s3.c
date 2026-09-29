#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_highest_unset_bit(uint32_t value)
{
    uint32_t bit = UINT32_C(1);

    while ((value & bit) != 0U && bit <= (UINT32_MAX >> 1)) {
        bit <<= 1;
    }

    return value | bit;
}

int main(void)
{
    uintmax_t input;
    int ch;

    errno = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &input) != 1 ||
        errno == ERANGE ||
        input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_highest_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}