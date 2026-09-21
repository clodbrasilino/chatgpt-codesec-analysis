#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_with_colons(const char *string, size_t length, char **output)
{
    char *copy;
    size_t i;

    if (string == NULL || output == NULL) {
        return EINVAL;
    }

    *output = NULL;

    if (length == SIZE_MAX) {
        return ENOMEM;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < length; ++i) {
        char character = string[i];

        copy[i] = character == ' ' || character == ',' || character == '.'
                      ? ':'
                      : character;
    }

    copy[length] = '\0';
    *output = copy;

    return 0;
}

int main(int argc, char **argv)
{
    char *result_string = NULL;
    size_t input_length;
    int result;

    if (argc != 2) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);
    result = replace_with_colons(argv[1], input_length, &result_string);

    if (result != 0) {
        if (fprintf(stderr, "Replacement failed: %s\n", strerror(result)) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (puts(result_string) == EOF) {
        free(result_string);
        return EXIT_FAILURE;
    }

    free(result_string);
    return EXIT_SUCCESS;
}