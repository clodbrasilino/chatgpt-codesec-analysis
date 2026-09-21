#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_to_lower(const char *input, size_t input_size)
{
    size_t length = 0U;
    char *output;

    if (input == NULL || input_size == 0U) {
        return NULL;
    }

    while (length < input_size && input[length] != '\0') {
        ++length;
    }

    if (length == input_size) {
        return NULL;
    }

    output = malloc(length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        output[i] = (char)tolower((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *lowercase;
    size_t input_size;

    if (argc != 2) {
        const char *program =
            (argc > 0 && argv != NULL && argv[0] != NULL) ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input_size = strlen(argv[1]);

    if (input_size == SIZE_MAX) {
        fprintf(stderr, "Input is too large.\n");
        return EXIT_FAILURE;
    }

    lowercase = string_to_lower(argv[1], input_size + 1U);
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