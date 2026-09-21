#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *string,
                          size_t length,
                          unsigned char *character,
                          size_t *count)
{
    size_t frequencies[256] = {0};
    size_t max_count = 0;
    unsigned char most_common = 0;

    if (string == NULL || character == NULL || count == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char value = string[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    for (size_t i = 0; i < 256; ++i) {
        if (frequencies[i] > max_count) {
            max_count = frequencies[i];
            most_common = (unsigned char)i;
        }
    }

    *character = most_common;
    *count = max_count;
    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    unsigned char *input = malloc(MAX_INPUT_LENGTH);
    size_t length = 0;
    unsigned char character;
    size_t count;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_LENGTH) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (length == MAX_INPUT_LENGTH) {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            free(input);
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (length == 0) {
        free(input);
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (most_common_character(input, length, &character, &count) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (character >= 32U && character <= 126U) {
        printf("Most common character: '%c'\nCount: %zu\n",
               (int)character, count);
    } else {
        printf("Most common character: 0x%02X\nCount: %zu\n",
               (unsigned int)character, count);
    }

    free(input);
    return EXIT_SUCCESS;
}