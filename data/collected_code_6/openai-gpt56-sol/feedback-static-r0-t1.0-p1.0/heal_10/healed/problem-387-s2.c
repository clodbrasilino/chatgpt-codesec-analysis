#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int is_hex_even(const char *hex, size_t length, int *is_even)
{
    size_t begin = 0;
    size_t end = length;
    unsigned char last;

    if (hex == NULL || is_even == NULL || length == 0) {
        return 0;
    }

    while (begin < end && isspace((unsigned char)hex[begin])) {
        ++begin;
    }

    while (end > begin && isspace((unsigned char)hex[end - 1])) {
        --end;
    }

    if (end - begin >= 2 &&
        hex[begin] == '0' &&
        (hex[begin + 1] == 'x' || hex[begin + 1] == 'X')) {
        begin += 2;
    }

    if (begin == end) {
        return 0;
    }

    for (size_t i = begin; i < end; ++i) {
        if (!isxdigit((unsigned char)hex[i])) {
            return 0;
        }
    }

    last = (unsigned char)tolower((unsigned char)hex[end - 1]);
    *is_even = last == '0' || last == '2' || last == '4' ||
               last == '6' || last == '8' || last == 'a' ||
               last == 'c' || last == 'e';

    return 1;
}

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int ch;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used >= MAX_INPUT_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && used == 0) {
        free(buffer);
        return 2;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int even;
    int status = read_line(&input, &length);

    if (status == -1) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 2 || !is_hex_even(input, length, &even)) {
        free(input);
        fputs("Invalid hexadecimal number.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(even ? "Even" : "Odd");
    free(input);

    return EXIT_SUCCESS;
}