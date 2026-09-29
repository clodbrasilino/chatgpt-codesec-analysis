#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_lowercase_substrings(const char *input, char **output)
{
    size_t input_length;
    size_t source_offset;
    size_t destination_offset;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return -1;
    }

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
    char *output = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (remove_lowercase_substrings(argv[1], &output) != 0) {
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