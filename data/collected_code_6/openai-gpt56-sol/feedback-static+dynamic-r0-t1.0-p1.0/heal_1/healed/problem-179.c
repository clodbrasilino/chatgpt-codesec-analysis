#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(uint64_t number)
{
    uint64_t digits[20] = {0};
    uint64_t sequence[20] = {0};
    size_t digit_count = 0;
    uint64_t value = number;

    if (number < 10) {
        return false;
    }

    do {
        if (digit_count >= sizeof digits / sizeof digits[0]) {
            return false;
        }

        digits[digit_count++] = value % UINT64_C(10);
        value /= UINT64_C(10);
    } while (value != 0);

    for (size_t i = 0; i < digit_count; ++i) {
        sequence[i] = digits[digit_count - 1 - i];
    }

    size_t index = 0;

    for (;;) {
        uint64_t next = 0;

        for (size_t i = 0; i < digit_count; ++i) {
            const uint64_t term = sequence[(index + i) % digit_count];

            if (next > UINT64_MAX - term) {
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

        sequence[index] = next;
        index = (index + 1) % digit_count;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long parsed_value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed_value > UINT64_MAX) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    const uint64_t number = (uint64_t)parsed_value;

    printf("%" PRIu64 " is %sa Keith number.\n",
           number,
           is_keith_number(number) ? "" : "not ");

    return EXIT_SUCCESS;
}