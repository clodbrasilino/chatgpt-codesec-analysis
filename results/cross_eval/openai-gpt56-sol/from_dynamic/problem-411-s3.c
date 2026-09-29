#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_len;
    size_t src;
    size_t dst;
    int capitalize;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    src = 0;
    dst = 0;
    capitalize = 1;

    while (src < input_len) {
        unsigned char ch = (unsigned char)input[src++];

        if (ch == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize && isalnum(ch)) {
            ch = (unsigned char)toupper(ch);
        }

        output[dst++] = (char)ch;
        capitalize = 0;
    }

    output[dst] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *camel_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}