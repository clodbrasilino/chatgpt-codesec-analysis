#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int camel_to_snake(const char *input, char **output)
{
    char *result;
    size_t input_len;
    size_t capacity;
    size_t source_pos;
    size_t dest_pos = 0U;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_len = strlen(input);

    if (input_len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = input_len * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (source_pos = 0U; source_pos < input_len; ++source_pos) {
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

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (camel_to_snake(argv[1], &snake_case) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    puts(snake_case);
    free(snake_case);

    return EXIT_SUCCESS;
}