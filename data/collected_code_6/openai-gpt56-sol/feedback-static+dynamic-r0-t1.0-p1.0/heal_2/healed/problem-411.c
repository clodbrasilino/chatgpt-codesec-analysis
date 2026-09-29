#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_length;
    size_t read_pos;
    size_t write_pos;
    int capitalize;
    char *output;

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

    read_pos = 0;
    write_pos = 0;
    capitalize = 1;

    while (read_pos < input_length) {
        unsigned char ch = (unsigned char)input[read_pos++];

        if (ch == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize) {
            ch = (unsigned char)toupper(ch);
        }

        output[write_pos++] = (char)ch;
        capitalize = 0;
    }

    output[write_pos] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc == 2) {
        result = snake_to_camel(argv[1]);
    } else {
        char input[4096];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            return EXIT_FAILURE;
        }

        input[strcspn(input, "\r\n")] = '\0';
        result = snake_to_camel(input);
    }

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}