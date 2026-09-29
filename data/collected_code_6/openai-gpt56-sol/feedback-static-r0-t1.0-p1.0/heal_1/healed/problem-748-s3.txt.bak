#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int add_spaces_before_capitals(const char *input, char **output)
{
    size_t input_len;
    size_t capacity;
    size_t write_pos = 0;
    char *result;

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

    for (size_t read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (read_pos > 0U) {
            unsigned char previous = (unsigned char)input[read_pos - 1U];

            if (((previous >= 'a' && previous <= 'z') ||
                 (previous >= '0' && previous <= '9')) &&
                current >= 'A' && current <= 'Z') {
                result[write_pos++] = ' ';
            }
        }

        result[write_pos++] = input[read_pos];
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char input[4096];
    char *output = NULL;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    {
        size_t length = strlen(input);

        if (length > 0U && input[length - 1U] == '\n') {
            input[--length] = '\0';

            if (length > 0U && input[length - 1U] == '\r') {
                input[length - 1U] = '\0';
            }
        } else if (!feof(stdin)) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            return EXIT_FAILURE;
        }
    }

    if (add_spaces_before_capitals(input, &output) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}