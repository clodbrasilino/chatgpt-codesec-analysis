#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_len;
    size_t read_pos = 0;
    size_t write_pos = 0;
    char *output;
    int capitalize = 1;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len > SIZE_MAX - 1) {
        return NULL;
    }

    output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (read_pos < input_len) {
        unsigned char ch = (unsigned char)input[read_pos++];

        if (ch == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize && isalnum(ch)) {
            ch = (unsigned char)toupper(ch);
        }

        output[write_pos++] = (char)ch;
        capitalize = 0;
    }

    output[write_pos] = '\0';
    return output;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
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