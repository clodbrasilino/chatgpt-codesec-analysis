#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0U;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin]) != 0) {
        ++begin;
    }

    while (begin < end && isspace((unsigned char)hex[end - 1U]) != 0) {
        --end;
    }

    if (begin == end) {
        return 0;
    }

    if (end - begin >= 2U &&
        hex[begin] == '0' &&
        (hex[begin + 1U] == 'x' || hex[begin + 1U] == 'X')) {
        begin += 2U;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (isxdigit((unsigned char)hex[i]) == 0) {
            return 0;
        }
    }

    last = (unsigned char)hex[end - 1U];
    *is_even = last == (unsigned char)'0' ||
               last == (unsigned char)'2' ||
               last == (unsigned char)'4' ||
               last == (unsigned char)'6' ||
               last == (unsigned char)'8' ||
               last == (unsigned char)'A' ||
               last == (unsigned char)'C' ||
               last == (unsigned char)'E' ||
               last == (unsigned char)'a' ||
               last == (unsigned char)'c' ||
               last == (unsigned char)'e';

    return 1;
}

static int read_input(char **input, size_t *length)
{
    char *buffer;
    size_t capacity = 128U;
    size_t used = 0U;
    int ch;

    if (input == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used >= INPUT_CAPACITY) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            free(buffer);

            if (ch == EOF && ferror(stdin) != 0) {
                return -1;
            }

            return 0;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity = capacity * 2U;
            char *new_buffer;

            if (new_capacity > INPUT_CAPACITY + 1U) {
                new_capacity = INPUT_CAPACITY + 1U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin) != 0) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && used == 0U) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *input = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int is_even = 0;
    int status;

    status = read_input(&input, &length);
    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Invalid hexadecimal number\n", stderr);
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