#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const unsigned char *string, size_t length)
{
    size_t i;

    if (string == NULL && length != 0) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (printf("%u\n", (unsigned int)string[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character = EOF;

    for (;;) {
        unsigned char *new_string;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(string);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof *string) {
                free(string);
                return EXIT_FAILURE;
            }

            new_string = realloc(string, new_capacity * sizeof *string);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        free(string);
        return EXIT_FAILURE;
    }

    if (print_ascii_values(string, length) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}