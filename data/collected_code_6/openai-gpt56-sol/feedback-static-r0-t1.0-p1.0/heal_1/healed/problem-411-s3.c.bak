#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_len;
    size_t src = 0;
    size_t dst = 0;
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

int main(int argc, char *const argv[])
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