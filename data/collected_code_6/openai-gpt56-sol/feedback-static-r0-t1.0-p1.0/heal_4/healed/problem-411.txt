#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_size)
{
    const char *end;
    const char *src;
    char *output;
    char *dst;
    size_t input_length;

    if (input == NULL || input_size == 0) {
        return NULL;
    }

    end = memchr(input, '\0', input_size);
    if (end == NULL) {
        return NULL;
    }

    input_length = (size_t)(end - input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    src = input;
    dst = output;

    while (src < end) {
        if (*src == '_' && end - src > 1 &&
            isalnum((unsigned char)src[1]) != 0) {
            *dst++ = (char)toupper((unsigned char)src[1]);
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    const char *program = "program";
    const char *argument;
    const char *argument_end;
    char *result;
    size_t input_size;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    argument = argv[1];
    argument_end = strchr(argument, '\0');
    input_size = (size_t)(argument_end - argument) + 1;

    result = snake_to_camel(argument, input_size);
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