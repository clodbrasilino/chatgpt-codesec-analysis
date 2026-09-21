#include <stdint.h>
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
            result[destination_offset++] = (char)character;
        }
    }

    result[destination_offset] = '\0';
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *input;
    char *result;
    size_t input_length;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strnlen(input, SIZE_MAX);

    if (input_length == SIZE_MAX ||
        remove_lowercase_substrings(input, input_length, &result) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}