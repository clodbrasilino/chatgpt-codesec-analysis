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
    int ch;
    intmax_t value;
    char *end;
    char buffer[64];
    size_t length = 0;

    if (result == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 < sizeof buffer) {
            buffer[length++] = (char)ch;
        } else {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);
            return false;
        }
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        return false;
    }

    buffer[length] = '\0';

    errno = 0;
    value = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        return false;
    }

    while (*end != '\0' && is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (!is_space_character(ch)) {
            return false;
        }
    }

    if (ferror(stdin)) {
        return false;
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