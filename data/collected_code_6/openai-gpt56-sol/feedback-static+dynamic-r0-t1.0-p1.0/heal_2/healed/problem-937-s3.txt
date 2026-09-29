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
        if (frequencies[string[i]] == SIZE_MAX) {
            return -1;
        }
        ++frequencies[string[i]];
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
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char character = 0;
    size_t count = 0;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof *input) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            unsigned char *new_input =
                realloc(input, new_capacity * sizeof *input);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 ||
        most_common_character(input, length, &character, &count) != 0) {
        free(input);
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (character >= 32 && character <= 126) {
        printf("Most common character: '%c'\nCount: %zu\n",
               (int)character, count);
    } else {
        printf("Most common character: 0x%02X\nCount: %zu\n",
               (unsigned int)character, count);
    }

    free(input);
    return EXIT_SUCCESS;
}