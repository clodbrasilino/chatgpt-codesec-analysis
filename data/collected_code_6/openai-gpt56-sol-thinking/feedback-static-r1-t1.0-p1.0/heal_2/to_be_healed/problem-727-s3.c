#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_non_alphanumeric(char *text, size_t length)
{
    size_t read_index;
    size_t write_index = 0;

    if (text == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)text[read_index];

        if (isalnum(character)) {
            text[write_index++] = (char)character;
        }
    }

    text[write_index] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    size_t length;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <text>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(argv[1]);

    if (remove_non_alphanumeric(argv[1], length) != 0) {
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