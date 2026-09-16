#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(uint64_t number)
{
    uint64_t sequence[20] = {0};
    uint64_t value = number;
    size_t digit_count = 0;

    if (number < 10) {
        return false;
    }

    do {
        ++digit_count;
        value /= 10;
    } while (value != 0);

    value = number;

    for (size_t i = digit_count; i > 0; --i) {
        sequence[i - 1] = value % 10;
        value /= 10;
    }

    size_t index = digit_count;

    for (;;) {
        uint64_t next = 0;

        for (size_t i = 0; i < digit_count; ++i) {
            uint64_t term =
                sequence[(index - digit_count + i) % digit_count];

            if (term > UINT64_MAX - next) {
                return false;
            }

            next += term;
        }

        if (next == number) {
            return true;
        }

        if (next > number) {
            return false;
        }

        sequence[index % digit_count] = next;
        ++index;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)parsed_value;

    printf("%" PRIu64 " is %sa Keith number.\n",
           number,
           is_keith_number(number) ? "" : "not ");

    return EXIT_SUCCESS;
}