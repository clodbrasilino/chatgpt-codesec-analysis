#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = number < UINT64_C(4294967295)
                        ? number
                        : UINT64_C(4294967295);

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;

        if (mid != 0 && mid > number / mid) {
            high = mid - 1;
        } else {
            uint64_t square = mid * mid;

            if (square == number) {
                return true;
            }

            low = mid + 1;
        }
    }

    return false;
}

static bool read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return false;
    }

    for (length = 0; length < size && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return true;
        }
    }

    if (length < size - 1 || feof(stdin)) {
        return true;
    }

    return false;
}

static bool is_space_character(char character)
{
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r' || character == '\f' || character == '\v';
}

static bool parse_uint64(const char *input, uint64_t *result)
{
    const char *cursor;
    char *end;
    uintmax_t value;

    if (input == NULL || result == NULL) {
        return false;
    }

    cursor = input;
    while (is_space_character(*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return false;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        return false;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return false;
    }

    *result = (uint64_t)value;
    return true;
}

int main(void)
{
    char input[128];
    uint64_t value;

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    if (!parse_uint64(input, &value)) {
        return EXIT_FAILURE;
    }

    puts(is_perfect_square(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}