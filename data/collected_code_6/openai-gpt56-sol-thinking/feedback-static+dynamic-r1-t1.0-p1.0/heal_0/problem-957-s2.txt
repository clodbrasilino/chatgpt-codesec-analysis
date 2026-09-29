#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char input[128];
    char *start;
    char *end;
    uintmax_t parsed_value;
    unsigned int position;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed_value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    position = rightmost_set_bit_position((uint64_t)parsed_value);

    if (printf("%u\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}