#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    bool matched = matches_pattern(input);
    free(input);

    if (fputs(matched ? "Match\n" : "No match\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}