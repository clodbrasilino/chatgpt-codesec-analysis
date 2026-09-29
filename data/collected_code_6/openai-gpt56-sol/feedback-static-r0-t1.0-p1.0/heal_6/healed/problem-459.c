#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input,
                                       size_t input_length,
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
        unsigned char c = (unsigned char)input[source_offset];

        if (c < (unsigned char)'A' || c > (unsigned char)'Z') {
            result[destination_offset++] = (char)c;
        }
    }

    result[destination_offset] = '\0';
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program;
    char *result;
    size_t input_length;

    program = (argc > 0 && argv != NULL && argv[0] != NULL)
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input_length = strnlen(argv[1], SIZE_MAX);
    if (input_length == SIZE_MAX) {
        fprintf(stderr, "Invalid input string.\n");
        return EXIT_FAILURE;
    }

    result = NULL;
    if (remove_uppercase_substrings(argv[1], input_length, &result) != 0) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}