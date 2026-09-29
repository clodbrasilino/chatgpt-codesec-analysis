#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_inner_bits(uint32_t value)
{
    if (value <= UINT32_C(1)) {
        return value;
    }

    uint32_t highest_bit = UINT32_C(1);

    while (highest_bit <= value / UINT32_C(2)) {
        highest_bit <<= 1;
    }

    return value ^ (highest_bit - UINT32_C(2));
}

static int read_uint32(uint32_t *value)
{
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return 0;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return 0;
        }
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT32_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint32_t)parsed;
    return 1;
}

int main(void)
{
    uint32_t value;

    if (!read_uint32(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n", toggle_inner_bits(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}