#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int remove_non_alphanumeric(char *text)
{
    char *read_ptr;
    char *write_ptr;

    if (text == NULL) {
        return -1;
    }

    read_ptr = text;
    write_ptr = text;

    while (*read_ptr != '\0') {
        unsigned char character = (unsigned char)*read_ptr++;

        if (isalnum(character)) {
            *write_ptr++ = (char)character;
        }
    }

    *write_ptr = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        program_name = argc > 0 && argv != NULL && argv[0] != NULL
                           ? argv[0]
                           : "program";

        if (fprintf(stderr, "Usage: %s <text>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(argv[1]) != 0) {
        if (fprintf(stderr, "Failed to process input\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}