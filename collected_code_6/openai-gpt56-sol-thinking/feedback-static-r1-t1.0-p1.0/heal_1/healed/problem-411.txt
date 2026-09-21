#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    char *output;
    size_t input_length;
    size_t input_index = 0;
    size_t output_index = 0;

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

    while (input_index < input_length) {
        if (input[input_index] == '_') {
            size_t next = input_index + 1;

            while (next < input_length && input[next] == '_') {
                ++next;
            }

            if (next < input_length &&
                isalnum((unsigned char)input[next]) != 0) {
                output[output_index++] =
                    (char)toupper((unsigned char)input[next]);
                input_index = next + 1;
                continue;
            }
        }

        output[output_index++] = input[input_index++];
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *camel_case;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s snake_case_string\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        if (fputs("Conversion failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputs(camel_case, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}