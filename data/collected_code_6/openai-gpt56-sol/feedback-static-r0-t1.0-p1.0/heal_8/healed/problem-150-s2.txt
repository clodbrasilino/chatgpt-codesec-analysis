#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_in_sequence(uint64_t number)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;

    while (low <= high) {
        uint64_t middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            uint64_t square = middle * middle;

            if (square == number) {
                return true;
            }

            low = middle + 1;
        }
    }

    return false;
}

static bool read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return false;
            }
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

static bool is_space_without_newline(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\f' || ch == '\v';
}

int main(void)
{
    char *input = NULL;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    char *start = input;

    while (is_space_without_newline(*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (is_space_without_newline(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_in_sequence((uint64_t)value) ? "Present" : "Not present");

    free(input);
    return EXIT_SUCCESS;
}