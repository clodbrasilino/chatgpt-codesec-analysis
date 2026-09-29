#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

static bool parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return false;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return true;
}

static char *read_line(size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int ch;

    if (length == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (used == capacity - 1) {
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

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && used == 0) {
        free(buffer);
        return NULL;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t first;
    uint64_t second;
    size_t length;

    input = read_line(&length);
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &first) ||
        !parse_uint64(&cursor, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(differ_by_one_bit(first, second) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}