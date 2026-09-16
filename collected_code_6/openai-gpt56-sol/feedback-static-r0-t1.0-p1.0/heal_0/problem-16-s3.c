#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_lowercase_sequence(const char *text)
{
    size_t i = 0;
    int expect_letter = 1;
    int saw_underscore = 0;

    if (text == NULL || *text == '\0') {
        return 0;
    }

    while (text[i] != '\0') {
        unsigned char ch = (unsigned char)text[i];

        if (expect_letter) {
            if (!islower(ch)) {
                return 0;
            }
            expect_letter = 0;
        } else if (islower(ch)) {
        } else if (ch == '_') {
            expect_letter = 1;
            saw_underscore = 1;
        } else {
            return 0;
        }

        ++i;
    }

    return saw_underscore && !expect_letter;
}

static void find_sequences(const char *text)
{
    size_t start = 0;
    size_t i = 0;

    if (text == NULL) {
        return;
    }

    while (1) {
        unsigned char ch = (unsigned char)text[i];

        if (!(islower(ch) || ch == '_')) {
            if (i > start) {
                size_t length = i - start;
                char *candidate = malloc(length + 1);

                if (candidate == NULL) {
                    fputs("Memory allocation failed\n", stderr);
                    exit(EXIT_FAILURE);
                }

                memcpy(candidate, text + start, length);
                candidate[length] = '\0';

                if (is_lowercase_sequence(candidate)) {
                    puts(candidate);
                }

                free(candidate);
            }

            if (ch == '\0') {
                break;
            }

            start = i + 1;
        }

        ++i;
    }
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input\n", stderr);
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        fputs("Input is too long\n", stderr);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';
    find_sequences(input);

    return EXIT_SUCCESS;
}