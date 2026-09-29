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
            int lowercase = tolower(character);

            if (lowercase >= 'a' && lowercase <= 'z' &&
                (size_t)(lowercase - 'a') == i) {
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
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

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

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            resized = realloc(string, new_capacity);

            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    string[length] = '\0';

    if (printf("%zu\n", count_matching_positions(string)) < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}