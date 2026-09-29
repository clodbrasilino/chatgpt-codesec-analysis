#include <ctype.h>
#include <stdint.h>
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
        } else if (islower(ch)) {
            continue;
        } else if (ch == '_') {
            expect_letter = 1;
            saw_underscore = 1;
        } else {
            return 0;
        }
    }

    return saw_underscore && !expect_letter;
}

static int find_sequences(const char *text, size_t length)
{
    size_t start = 0;
    size_t i;

    if (text == NULL) {
        return 0;
    }

    for (i = 0; i <= length; ++i) {
        unsigned char ch = i < length ? (unsigned char)text[i] : '\0';

        if (!islower(ch) && ch != '_') {
            size_t sequence_length = i - start;

            if (sequence_length > 0 &&
                is_lowercase_sequence(text + start, sequence_length)) {
                if (fwrite(text + start, 1, sequence_length, stdout) !=
                        sequence_length ||
                    fputc('\n', stdout) == EOF) {
                    return -1;
                }
            }

            start = i + 1;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int result = EXIT_SUCCESS;

    for (;;) {
        size_t available;
        size_t bytes_read;
        void *newline;

        if (capacity - length < 2) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 256;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    fputs("Input is too long\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Memory allocation failed\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        available = capacity - length - 1;
        bytes_read = fread(input + length, 1, available, stdin);

        newline = memchr(input + length, '\n', bytes_read);
        if (newline != NULL) {
            length = (size_t)((char *)newline - input);
            break;
        }

        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stdin)) {
                fputs("Failed to read input\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    input[length] = '\0';

    if (find_sequences(input, length) != 0) {
        fputs("Failed to write output\n", stderr);
        result = EXIT_FAILURE;
    }

    free(input);
    return result;
}