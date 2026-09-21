#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *snake_to_camel(const char *input, size_t input_length)
{
    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t output_index = 0;
    int capitalize = 1;

    for (size_t input_index = 0; input_index < input_length; ++input_index) {
        unsigned char character = (unsigned char)input[input_index];

        if (character == '_') {
            capitalize = 1;
            continue;
        }

        if (capitalize) {
            character = (unsigned char)toupper(character);
            capitalize = 0;
        }

        output[output_index++] = (char)character;
    }

    output[output_index] = '\0';
    return output;
}

static int ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    size_t new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return 0;
    }

    char *resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return 0;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 1;
}

static char *read_line(FILE *stream, size_t *length)
{
    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;

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
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return NULL;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (used == SIZE_MAX ||
            !ensure_capacity(&buffer, &capacity, used + 1)) {
            free(buffer);
            return NULL;
        }

        buffer[used++] = (char)(unsigned char)character;
    }

    if (used == SIZE_MAX ||
        !ensure_capacity(&buffer, &capacity, used + 1)) {
        free(buffer);
        return NULL;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    size_t input_length;
    char *input = read_line(stdin, &input_length);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *output = snake_to_camel(input, input_length);
    free(input);

    if (output == NULL) {
        return EXIT_FAILURE;
    }

    int failed = fputs(output, stdout) == EOF ||
                 fputc('\n', stdout) == EOF;

    free(output);
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}