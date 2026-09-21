#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *insert_spaces_before_capitals(const char *input)
{
    size_t input_length = 0;
    size_t output_length = 0;
    size_t source_offset;
    size_t destination_offset = 0;
    char *result;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    while (input[input_length] != '\0') {
        size_t required = 1;

        if (isupper((unsigned char)input[input_length]) &&
            input_length > 0 &&
            !isspace((unsigned char)input[input_length - 1])) {
            required++;
        }

        if (output_length > SIZE_MAX - required) {
            errno = EOVERFLOW;
            return NULL;
        }

        output_length += required;

        if (input_length == SIZE_MAX) {
            errno = EOVERFLOW;
            return NULL;
        }

        input_length++;
    }

    if (output_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (source_offset = 0; source_offset < input_length; source_offset++) {
        unsigned char current = (unsigned char)input[source_offset];

        if (isupper(current) &&
            source_offset > 0 &&
            !isspace((unsigned char)input[source_offset - 1])) {
            result[destination_offset++] = ' ';
        }

        result[destination_offset++] = (char)current;
    }

    result[destination_offset] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("insert_spaces_before_capitals");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        perror("output");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}