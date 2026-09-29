#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    result = scanf("%" SCNuMAX, &input);

    if (result != 1 || errno == ERANGE || input > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
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