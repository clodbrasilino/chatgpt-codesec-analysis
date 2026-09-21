#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    const char *src;
    char *output;
    char *dst;
    size_t input_length;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    src = input;
    dst = output;

    while (*src != '\0') {
        if (*src == '_' && src[1] != '\0' &&
            isalnum((unsigned char)src[1])) {
            *dst++ = (char)toupper((unsigned char)src[1]);
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}