#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_lowercase_substrings(const char *input, size_t input_length,
                                       char **output)
{
    char *result;
    size_t source_offset;
    size_t destination_offset;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    destination_offset = 0;

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
    const char *program;
    const char *input;
    char *output;
    size_t input_length;

    program = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strnlen(input, SIZE_MAX);

    if (input_length == SIZE_MAX ||
        remove_lowercase_substrings(input, input_length, &output) != 0) {
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