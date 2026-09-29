#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    do {
        if (*str != '0' && *str != '1') {
            return 0;
        }
    } while (*++str != '\0');

    return 1;
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
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            char *temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                free(input);
                return EXIT_FAILURE;
            }
        } else if (next == EOF && ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    } else if (character == EOF && ferror(stdin)) {
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

    if (puts(is_binary_string(input) ? "Binary string" :
                                         "Not a binary string") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}