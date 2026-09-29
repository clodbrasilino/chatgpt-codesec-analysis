#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_one_less_than_twice_reverse(uint64_t number)
{
    uint64_t value = number;
    uint64_t reversed = 0;

    do {
        uint64_t digit = value % 10U;

        if (reversed > (UINT64_MAX - digit) / 10U) {
            return false;
        }

        reversed = reversed * 10U + digit;
        value /= 10U;
    } while (value != 0U);

    return reversed <= UINT64_MAX / 2U &&
           number == reversed * 2U - (reversed != 0U ? 1U : 0U) &&
           reversed != 0U;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    printf("%s\n",
           is_one_less_than_twice_reverse((uint64_t)parsed) ? "true" : "false");

    return EXIT_SUCCESS;
}