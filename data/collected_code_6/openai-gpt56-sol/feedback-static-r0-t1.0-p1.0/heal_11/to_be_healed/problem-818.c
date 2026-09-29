#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_lowercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (islower((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *temporary;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Failed to allocate input buffer\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate input buffer\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (printf("%zu\n", count_lowercase(input)) < 0) {
        free(input);
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}