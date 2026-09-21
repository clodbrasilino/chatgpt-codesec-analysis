#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (unsigned char *)string;

    while (*current != '\0') {
        *current = (unsigned char)tolower(*current);
        ++current;
    }

    return 0;
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
    while ((character = fgetc(stdin)) != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > (SIZE_MAX / 2)) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity == 0 ? 128 : capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && character == EOF) {
        free(input);
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    if (string_to_lower(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fputs(input, stdout) == EOF) {
        perror("fputs");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}