#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin;
    size_t end;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    begin = 0;
    end = length;

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    if (begin < end &&
        hex[begin] == '0' &&
        end - begin > 1 &&
        (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
        begin += 2;
    }

    if (begin >= end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1];
    *is_even = (last == '0' || last == '2' || last == '4' ||
                last == '6' || last == '8' || last == 'a' ||
                last == 'c' || last == 'e' || last == 'A' ||
                last == 'C' || last == 'E');

    return 1;
}

static int read_line(char **buffer, size_t *length)
{
    char *line;
    size_t capacity;
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;
    line = NULL;
    capacity = 0;
    used = 0;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && line[used - 1] == '\r') {
        --used;
    }

    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            return 0;
        }
    }

    *buffer = line;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    size_t length;
    int is_even;

    if (!read_line(&input, &length)) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_hex_even(input, length, &is_even)) {
        free(input);
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    puts(is_even ? "Even" : "Odd");

    return EXIT_SUCCESS;
}