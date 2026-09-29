#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int replace_whitespace_and_underscores(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    for (current = (unsigned char *)string; *current != '\0'; ++current) {
        if (*current == '_') {
            *current = ' ';
        } else if (isspace(*current)) {
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
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        perror("getchar");
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

    if (replace_whitespace_and_underscores(input) != 0) {
        fprintf(stderr, "Unable to process the input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        perror("puts");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}