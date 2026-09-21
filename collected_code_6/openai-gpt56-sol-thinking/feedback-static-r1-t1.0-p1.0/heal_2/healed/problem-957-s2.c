#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_uint64_line(FILE *stream, uint64_t *value)
{
    enum input_state {
        INPUT_LEADING,
        INPUT_SIGN,
        INPUT_DIGITS,
        INPUT_TRAILING
    };

    enum input_state state = INPUT_LEADING;
    uint64_t result = UINT64_C(0);

    if (stream == NULL || value == NULL) {
        return 0;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) != 0) {
                return 0;
            }

            if (state == INPUT_DIGITS || state == INPUT_TRAILING) {
                *value = result;
                return 1;
            }

            return 0;
        }

        if (character == '\0') {
            return 0;
        }

        if (character == '\n') {
            if (state == INPUT_DIGITS || state == INPUT_TRAILING) {
                *value = result;
                return 1;
            }

            return 0;
        }

        switch (state) {
        case INPUT_LEADING:
            if (isspace((unsigned char)character) != 0) {
                break;
            }

            if (character == '-') {
                return 0;
            }

            if (character == '+') {
                state = INPUT_SIGN;
                break;
            }

            if (character < '0' || character > '9') {
                return 0;
            }

            result = (uint64_t)(character - '0');
            state = INPUT_DIGITS;
            break;

        case INPUT_SIGN:
            if (character < '0' || character > '9') {
                return 0;
            }

            result = (uint64_t)(character - '0');
            state = INPUT_DIGITS;
            break;

        case INPUT_DIGITS:
            if (character >= '0' && character <= '9') {
                uint64_t digit = (uint64_t)(character - '0');

                if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                    return 0;
                }

                result = result * UINT64_C(10) + digit;
                break;
            }

            if (isspace((unsigned char)character) != 0) {
                state = INPUT_TRAILING;
                break;
            }

            return 0;

        case INPUT_TRAILING:
            if (isspace((unsigned char)character) == 0) {
                return 0;
            }
            break;
        }
    }
}

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

int main(void)
{
    uint64_t value;
    unsigned int position;

    if (!read_uint64_line(stdin, &value)) {
        return EXIT_FAILURE;
    }

    position = rightmost_set_bit_position(value);

    if (printf("%u\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}