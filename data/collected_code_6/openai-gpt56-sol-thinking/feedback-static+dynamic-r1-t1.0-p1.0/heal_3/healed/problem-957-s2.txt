#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int rightmost_set_bit_position(uint64_t value)
{
    unsigned int position = 0U;

    while (value != UINT64_C(0)) {
        ++position;

        if ((value & UINT64_C(1)) != UINT64_C(0)) {
            return position;
        }

        value >>= 1U;
    }

    return 0U;
}

static int parse_uint64_line(uint64_t *result)
{
    enum parse_state {
        STATE_LEADING,
        STATE_SIGN,
        STATE_DIGITS,
        STATE_TRAILING
    };

    enum parse_state state = STATE_LEADING;
    uint64_t value = UINT64_C(0);

    if (result == NULL) {
        return 0;
    }

    for (;;) {
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin) != 0) {
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        switch (state) {
        case STATE_LEADING:
            if (isspace((unsigned char)ch) != 0) {
                continue;
            }

            if (ch == '+') {
                state = STATE_SIGN;
                continue;
            }

            if (ch < '0' || ch > '9') {
                return 0;
            }

            state = STATE_DIGITS;
            break;

        case STATE_SIGN:
            if (ch < '0' || ch > '9') {
                return 0;
            }

            state = STATE_DIGITS;
            break;

        case STATE_DIGITS:
            if (ch < '0' || ch > '9') {
                if (isspace((unsigned char)ch) == 0) {
                    return 0;
                }

                state = STATE_TRAILING;
                continue;
            }
            break;

        case STATE_TRAILING:
            if (isspace((unsigned char)ch) == 0) {
                return 0;
            }
            continue;
        }

        {
            uint64_t digit = (uint64_t)(ch - '0');

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                return 0;
            }

            value = value * UINT64_C(10) + digit;
        }
    }

    if (state != STATE_DIGITS && state != STATE_TRAILING) {
        return 0;
    }

    *result = value;
    return 1;
}

int main(void)
{
    uint64_t value;
    unsigned int position;

    if (parse_uint64_line(&value) == 0) {
        return EXIT_FAILURE;
    }

    position = rightmost_set_bit_position(value);

    if (printf("%u\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}