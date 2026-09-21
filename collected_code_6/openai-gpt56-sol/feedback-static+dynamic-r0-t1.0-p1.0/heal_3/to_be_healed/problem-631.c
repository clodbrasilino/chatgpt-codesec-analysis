#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int replace_whitespace_and_underscores(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *current = (unsigned char *)string;
         *current != '\0';
         ++current) {
        if (*current == '_') {
            *current = ' ';
        } else if (*current == ' ' || *current == '\t' ||
                   *current == '\n' || *current == '\r' ||
                   *current == '\f' || *current == '\v') {
            *current = '_';
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Unable to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (replace_whitespace_and_underscores(input) != 0) {
        free(input);
        fputs("Unable to process the input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        perror("puts");
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}