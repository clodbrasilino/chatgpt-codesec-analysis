#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int camel_to_snake(const char *input, size_t input_len, char **output)
{
    size_t capacity;
    size_t source_pos;
    size_t dest_pos = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    if (input_len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = input_len * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (source_pos = 0; source_pos < input_len; ++source_pos) {
        unsigned char current = (unsigned char)input[source_pos];

        if (source_pos > 0U &&
            isupper(current) &&
            (islower((unsigned char)input[source_pos - 1U]) ||
             isdigit((unsigned char)input[source_pos - 1U]))) {
            result[dest_pos++] = '_';
        }

        result[dest_pos++] = (char)tolower(current);
    }

    result[dest_pos] = '\0';
    *output = result;

    return 0;
}

int main(int argc, char *const argv[])
{
    char *snake_case = NULL;
    const char *input;
    size_t input_len = 0;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_len] != '\0') {
        if (input_len == SIZE_MAX) {
            fputs("Input is too long\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_len;
    }

    if (camel_to_snake(input, input_len, &snake_case) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    puts(snake_case);
    free(snake_case);

    return EXIT_SUCCESS;
}