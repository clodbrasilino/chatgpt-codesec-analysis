#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lowercase_sequence(const char *text, size_t length)
{
    size_t i;
    int expect_letter = 1;
    int saw_underscore = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)text[i];

        if (expect_letter) {
            if (!islower(ch)) {
                return 0;
            }
            expect_letter = 0;
        } else if (ch == '_') {
            expect_letter = 1;
            saw_underscore = 1;
        } else if (!islower(ch)) {
            return 0;
        }
    }

    return saw_underscore && !expect_letter;
}

static int print_sequence(const char *text, size_t length)
{
    if (length != 0 && fwrite(text, 1, length, stdout) != length) {
        return 0;
    }

    return fputc('\n', stdout) != EOF;
}

static int find_sequences(const char *text)
{
    const char *start;
    const char *current;

    if (text == NULL) {
        return 0;
    }

    start = text;

    for (current = text;; ++current) {
        unsigned char ch = (unsigned char)*current;

        if (!islower(ch) && ch != '_') {
            size_t length = (size_t)(current - start);

            if (is_lowercase_sequence(start, length) &&
                !print_sequence(start, length)) {
                return 0;
            }

            if (ch == '\0') {
                return 1;
            }

            start = current + 1;
        }
    }
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
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

        buffer[length++] = (char)ch;
    }

    if (length != 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_sequences(input)) {
        free(input);
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}