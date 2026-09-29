#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_len;
    size_t read_pos = 0;
    size_t write_pos = 0;
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

    while (read_pos < input_len) {
        if (input[read_pos] == '_') {
            size_t next = read_pos;

            while (next < input_len && input[next] == '_') {
                ++next;
            }

            if (next < input_len &&
                isalnum((unsigned char)input[next]) != 0) {
                output[write_pos++] =
                    (char)toupper((unsigned char)input[next]);
                read_pos = next + 1;
                continue;
            }
        }

        output[write_pos++] = input[read_pos++];
    }

    output[write_pos] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL
                                  ? argv[0]
                                  : "snake_to_camel";
        fprintf(stderr, "Usage: %s snake_case_string\n", program);
        return EXIT_FAILURE;
    }

    result = snake_to_camel(argv[1]);
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