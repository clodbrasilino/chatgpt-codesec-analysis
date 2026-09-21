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

    if (scanf("%" SCNuMAX, &input) != 1 ||
        errno == ERANGE ||
        input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_highest_unset_bit((uint32_t)input));
    return EXIT_SUCCESS;
}