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

static bool is_space_character(char character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
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
    value = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor || value > UINT64_MAX) {
        return false;
    }

    while (is_space_character(*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *result = (uint64_t)value;
    return true;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = NULL;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    uint64_t value;
    bool valid;

    input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    valid = parse_uint64(input, &value);
    free(input);

    if (!valid) {
        return EXIT_FAILURE;
    }

    if (puts(is_perfect_square(value) ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}