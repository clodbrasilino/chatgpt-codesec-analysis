#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_idx = 0;
    size_t i;
    int capitalize_next = 1;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        if (input[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[result_idx] = (char)toupper((unsigned char)input[i]);
                capitalize_next = 0;
            } else {
                result[result_idx] = input[i];
            }
            result_idx++;
        }
    }

    result[result_idx] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    char buffer[4096];
    const char *input;
    char *output;

    if (argc > 1) {
        input = argv[1];
    } else {
        size_t len;

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return EXIT_FAILURE;
        }
        len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[--len] = '\0';
        }
        input = buffer;
    }

    output = snake_to_camel(input);
    if (output == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    fflush(stdout);

    free(output);
    return EXIT_SUCCESS;
}