#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void print_sequence(const char *text, size_t length)
{
    if (length > 0) {
        fwrite(text, 1, length, stdout);
    }
    fputc('\n', stdout);
}

static void find_sequences(const char *text)
{
    const char *start;
    const char *current;

    if (text == NULL) {
        return;
    }

    start = text;
    current = text;

    for (;;) {
        unsigned char ch = (unsigned char)*current;

        if (!(islower(ch) || ch == '_')) {
            size_t length = (size_t)(current - start);

            if (is_lowercase_sequence(start, length)) {
                print_sequence(start, length);
            }

            if (ch == '\0') {
                break;
            }

            start = current + 1;
        }

        ++current;
    }
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

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

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (length == capacity) {
        char *new_buffer;

        if (capacity == SIZE_MAX) {
            free(buffer);
            return NULL;
        }

        new_buffer = realloc(buffer, capacity + 1);
        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
        }
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

    find_sequences(input);
    free(input);

    if (ferror(stdout)) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}