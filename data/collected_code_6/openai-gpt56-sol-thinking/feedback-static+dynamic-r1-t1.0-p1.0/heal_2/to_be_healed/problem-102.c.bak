#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input)
{
    size_t input_length;
    size_t read_index;
    size_t write_index = 0;
    int capitalize_next = 1;
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

    for (read_index = 0; read_index < input_length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (character == '_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next) {
            character = (unsigned char)toupper(character);
            capitalize_next = 0;
        }

        output[write_index++] = (char)character;
    }

    output[write_index] = '\0';
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char *camel_case;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1]);
    if (camel_case == NULL) {
        fprintf(stderr, "Failed to convert string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}