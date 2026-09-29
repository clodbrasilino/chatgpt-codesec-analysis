#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_length;
    size_t read_pos;
    size_t write_pos = 0;
    int capitalize = 1;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_pos = 0; read_pos < input_length; ++read_pos) {
        unsigned char c = (unsigned char)input[read_pos];

        if (c == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize && isalnum(c)) {
            output[write_pos++] = (char)toupper(c);
            capitalize = 0;
        } else {
            output[write_pos++] = (char)c;
            capitalize = 0;
        }
    }

    output[write_pos] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = argv[1];
    result = snake_to_camel(input);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}