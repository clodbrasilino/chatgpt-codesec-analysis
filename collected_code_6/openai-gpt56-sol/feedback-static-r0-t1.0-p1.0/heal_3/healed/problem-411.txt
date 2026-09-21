#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_size)
{
    const char *src;
    const char *end;
    char *output;
    char *dst;
    size_t input_length;

    if (input == NULL) {
        return NULL;
    }

    end = memchr(input, '\0', input_size);
    if (end == NULL) {
        return NULL;
    }

    input_length = (size_t)(end - input);
    if (input_length > SIZE_MAX - 1) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    src = input;
    dst = output;

    while (src < end) {
        if (*src == '_' &&
            src + 1 < end &&
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
    const char *program = "program";
    char *result;
    size_t input_size;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    input_size = strlen(argv[1]) + 1;
    result = snake_to_camel(argv[1], input_size);
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