#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const unsigned char *string, size_t length)
{
    size_t i;

    if (string == NULL) {
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
    unsigned char *string;
    size_t length = 0;
    size_t capacity = 128;
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;
    int result = EXIT_SUCCESS;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                perror("fgetc");
                result = EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity > SIZE_MAX / 2) {
                result = EXIT_FAILURE;
                break;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                result = EXIT_FAILURE;
                break;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (unsigned char)character;
    }

    if (result == EXIT_SUCCESS &&
        print_ascii_values(string, length) != 0) {
        result = EXIT_FAILURE;
    }

    free(string);
    return result;
}