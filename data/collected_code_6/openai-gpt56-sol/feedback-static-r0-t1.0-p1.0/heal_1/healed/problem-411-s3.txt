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
    char *output;

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

    src = 0;
    dst = 0;

    while (src < input_len) {
        if (input[src] == '_' &&
            src + 1 < input_len &&
            isalnum((unsigned char)input[src + 1])) {
            output[dst++] = (char)toupper((unsigned char)input[src + 1]);
            src += 2;
        } else {
            output[dst++] = input[src++];
        }
    }

    output[dst] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *camel_case;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}