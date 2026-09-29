#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

static bool is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static bool read_int64(int64_t *result)
{
    intmax_t value;
    int ch;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[32];
    size_t length = 0;
    bool overflow = false;

    if (result == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && is_space_character(ch));

    if (ch == EOF) {
        return false;
    }

    do {
        if (length + 1 < sizeof token) {
            token[length++] = (char)ch;
        } else {
            overflow = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && !is_space_character(ch));

    while (ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != EOF && !is_space_character(ch)) {
            return false;
        }
    }

    if (ferror(stdin) || overflow || length == 0) {
        return false;
    }

    token[length] = '\0';

    {
        char *end;

        errno = 0;
        value = strtoimax(token, &end, 10);

        if (end == token || *end != '\0' || errno == ERANGE ||
            value < INT64_MIN || value > INT64_MAX) {
            return false;
        }
    }

    *result = (int64_t)value;
    return true;
}

int main(void)
{
    int64_t value;

    if (!read_int64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}