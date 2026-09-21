#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, size_t input_length,
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

        if (character < (unsigned char)'A' ||
            character > (unsigned char)'Z') {
            result[destination_offset++] = (char)character;
        }
    }

    result[destination_offset] = '\0';
    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *result = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;
    size_t input_length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                           ? argv[0]
                           : "program";
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);

    if (remove_uppercase_substrings(argv[1], input_length, &result) != 0) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}