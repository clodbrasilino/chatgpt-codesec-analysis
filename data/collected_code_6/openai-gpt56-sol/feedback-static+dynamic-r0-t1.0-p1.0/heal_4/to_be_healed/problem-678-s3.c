#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_spaces(char *string)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string;
    size_t length = 0;
    size_t capacity = 128;
    int character = EOF;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
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

        string[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stdin)) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length == 0) {
            free(string);
            return EXIT_SUCCESS;
        }
    }

    string[length] = '\0';
    remove_spaces(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}