#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_size)
{
    const char *terminator;
    size_t input_len;
    size_t read_pos = 0;
    size_t write_pos = 0;
    char *output;
    int capitalize = 1;

    if (input == NULL) {
        return NULL;
    }

    terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    input_len = (size_t)(terminator - input);
    if (input_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (read_pos < input_len) {
        unsigned char ch = (unsigned char)input[read_pos++];

        if (ch == (unsigned char)'_') {
            capitalize = 1;
            continue;
        }

        if (capitalize != 0 && isalnum((int)ch) != 0) {
            ch = (unsigned char)toupper((int)ch);
        }

        output[write_pos++] = (char)ch;
        capitalize = 0;
    }

    output[write_pos] = '\0';
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