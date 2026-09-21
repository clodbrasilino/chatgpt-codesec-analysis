#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *to_uppercase(const char *input, size_t input_size)
{
    if (input == NULL) {
        return NULL;
    }

    const char *terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    size_t length = (size_t)(terminator - input);
    if (length == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        output[i] = (char)toupper((unsigned char)input[i]);
    }

    output[length] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    char *uppercase = to_uppercase(argv[1], strlen(argv[1]) + 1);
    if (uppercase == NULL) {
        fputs("Failed to convert string\n", stderr);
        return EXIT_FAILURE;
    }

    int result = puts(uppercase);
    free(uppercase);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}