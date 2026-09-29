#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *string_to_lower(const char *input)
{
    size_t length = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    while (input[length] != '\0') {
        if (length == SIZE_MAX - 1) {
            return NULL;
        }
        ++length;
    }

    output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        output[i] = (char)tolower((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *lowercase;
    const char *program;

    program = (argc > 0 && argv != NULL && argv[0] != NULL)
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    lowercase = string_to_lower(argv[1]);
    if (lowercase == NULL) {
        fprintf(stderr, "Failed to convert string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", lowercase) < 0) {
        free(lowercase);
        return EXIT_FAILURE;
    }

    free(lowercase);
    return EXIT_SUCCESS;
}