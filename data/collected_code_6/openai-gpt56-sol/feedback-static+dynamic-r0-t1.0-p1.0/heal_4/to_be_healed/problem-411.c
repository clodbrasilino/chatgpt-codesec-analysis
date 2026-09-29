#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    size_t read_pos;
    size_t write_pos = 0;
    int capitalize = 1;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_pos = 0; read_pos < input_length; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if (ch == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize) {
            ch = (unsigned char)toupper(ch);
        }

        output[write_pos++] = (char)ch;
        capitalize = 0;
    }

    output[write_pos] = '\0';
    return output;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF || ch == '\n' || ch == '\r') {
            if (ch == EOF && used == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    *length = used;
    return buffer;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *owned_input = NULL;
    char *result;
    size_t input_length;

    if (argc == 2) {
        input = argv[1];
        input_length = 0;

        while (input[input_length] != '\0') {
            if (input_length == SIZE_MAX) {
                return EXIT_FAILURE;
            }
            ++input_length;
        }
    } else if (argc == 1) {
        owned_input = read_line(stdin, &input_length);
        if (owned_input == NULL) {
            return EXIT_FAILURE;
        }
        input = owned_input;
    } else {
        return EXIT_FAILURE;
    }

    result = snake_to_camel(input, input_length);
    free(owned_input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}