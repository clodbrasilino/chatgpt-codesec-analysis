#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_occurring_character(const unsigned char *data, size_t length,
                                  unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    unsigned int max_character = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (unsigned int i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            max_character = i;
        }
    }

    *result = (unsigned char)max_character;
    return 1;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    unsigned char *input = malloc((size_t)MAX_INPUT_LENGTH);
    size_t length = 0;
    unsigned char result;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == (size_t)MAX_INPUT_LENGTH) {
            int discard;

            do {
                discard = fgetc(stdin);
            } while (discard != EOF && discard != '\n');

            if (ferror(stdin)) {
                perror("Failed to read input");
            } else {
                fputs("Input is too long.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        free(input);
        return EXIT_FAILURE;
    }

    if (!find_max_occurring_character(input, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (fputc((int)result, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        perror("Failed to write output");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}