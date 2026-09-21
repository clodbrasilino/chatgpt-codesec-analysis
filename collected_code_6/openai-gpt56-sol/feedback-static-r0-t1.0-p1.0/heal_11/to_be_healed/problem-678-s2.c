#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_spaces(char *string)
{
    char *destination = string;

    for (const char *source = string; *source != '\0'; ++source) {
        if (*source != ' ') {
            *destination++ = *source;
        }
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length > SIZE_MAX - 2) {
            free(string);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            char *temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(string);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        free(string);
        return EXIT_SUCCESS;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    string[length] = '\0';
    remove_spaces(string);

    if (puts(string) == EOF) {
        free(string);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}