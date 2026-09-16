#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_keith_number(uint64_t number)
{
    uint64_t digits[20];
    uint64_t sequence[20];
    size_t digit_count = 0U;
    uint64_t value = number;

    if (number < 10U) {
        return false;
    }

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (value > 0U) {
        digits[digit_count++] = value % 10U;
        value /= 10U;
    }

    for (size_t i = 0U; i < digit_count; ++i) {
        /* Possible weaknesses found:
         *  Uninitialized variable: digits
         *  Uninitialized variable: digits [uninitvar]
         */
        sequence[i] = digits[digit_count - 1U - i];
    }

    size_t index = digit_count;

    for (;;) {
        uint64_t next = 0U;

        for (size_t i = 0U; i < digit_count; ++i) {
            uint64_t term = sequence[(index - digit_count + i) % digit_count];

            if (UINT64_MAX - next < term) {
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
    unsigned long long parsed_value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    uint64_t number = (uint64_t)parsed_value;

    printf("%llu is %sa Keith number.\n",
           parsed_value,
           is_keith_number(number) ? "" : "not ");

    return EXIT_SUCCESS;
}