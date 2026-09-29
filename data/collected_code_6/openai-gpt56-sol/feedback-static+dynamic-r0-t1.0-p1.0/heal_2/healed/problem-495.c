#include <stdio.h>
#include <stdlib.h>

static int remove_lowercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    size_t source_offset;
    size_t destination_offset = 0;
    char *result;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (source_offset = 0; source_offset < input_length; ++source_offset) {
        unsigned char character = (unsigned char)input[source_offset];

        if (character < (unsigned char)'a' ||
            character > (unsigned char)'z') {
            result[destination_offset++] = input[source_offset];
        }
    }

    result[destination_offset] = '\0';
    *output = result;

    return 0;
}

int main(int argc, char *argv[])
{
    char *output = NULL;
    size_t input_length = 0;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    while (argv[1][input_length] != '\0') {
        if (input_length == SIZE_MAX) {
            fputs("Input string is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    if (remove_lowercase_substrings(argv[1], input_length, &output) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}