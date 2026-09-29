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
    unsigned char character;
    size_t count;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof *input) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            unsigned char *new_input = realloc(input,
                                               new_capacity * sizeof *input);
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

    if (most_common_character(input, length, &character, &count) != 0) {
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