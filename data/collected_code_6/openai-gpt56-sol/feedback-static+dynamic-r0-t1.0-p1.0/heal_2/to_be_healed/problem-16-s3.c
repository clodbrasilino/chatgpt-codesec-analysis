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

static int find_sequences(const char *text)
{
    size_t start = 0;
    size_t i;

    if (text == NULL) {
        return 0;
    }

    for (i = 0;; ++i) {
        unsigned char ch = (unsigned char)text[i];

        if (!islower(ch) && ch != '_') {
            size_t length = i - start;

            if (length > 0 && is_lowercase_sequence(text + start, length)) {
                if (fwrite(text + start, 1, length, stdout) != length ||
                    fputc('\n', stdout) == EOF) {
                    return -1;
                }
            }

            if (ch == '\0') {
                break;
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
    int ch;
    int result = EXIT_SUCCESS;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == capacity) {
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

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            fputs("Input is too long\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (find_sequences(input) != 0) {
        fputs("Failed to write output\n", stderr);
        result = EXIT_FAILURE;
    }

    free(input);
    return result;
}