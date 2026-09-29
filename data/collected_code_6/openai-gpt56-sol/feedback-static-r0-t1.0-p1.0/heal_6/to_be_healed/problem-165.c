#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (isalpha(character)) {
            int lower = tolower(character);

            if (lower >= 'a' && lower <= 'z' &&
                i == (size_t)(lower - 'a')) {
                ++count;
            }
        }
    }

    return count;
}

int main(void)
{
    size_t length = 0;
    size_t capacity = 128;
    char *string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin) || length == 0) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(string);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *temporary = realloc(string, new_capacity);

            if (temporary == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    string[length] = '\0';

    size_t result = count_matching_positions(string);
    free(string);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}