#include <ctype.h>
#include <limits.h>
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

static char *read_line(size_t *length)
{
    if (length == NULL) {
        return NULL;
    }

    *length = 0;

    size_t capacity = 128;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        size_t available = capacity - *length;

        if (available < 2) {
            if (capacity > SIZE_MAX / 2 ||
                capacity * 2 > (size_t)INT_MAX) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
            available = capacity - *length;
        }

        if (fgets(buffer + *length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || *length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        size_t index = *length;
        while (index < capacity && buffer[index] != '\0' &&
               buffer[index] != '\n' && buffer[index] != '\r') {
            ++index;
        }

        if (index < capacity &&
            (buffer[index] == '\n' || buffer[index] == '\r')) {
            if (buffer[index] == '\r') {
                int next = fgetc(stdin);
                if (next != '\n' && next != EOF) {
                    if (ungetc(next, stdin) == EOF) {
                        free(buffer);
                        return NULL;
                    }
                }
            }

            *length = index;
            buffer[index] = '\0';
            return buffer;
        }

        *length = index;

        if (feof(stdin)) {
            break;
        }
    }

    buffer[*length] = '\0';
    return buffer;
}

int main(void)
{
    size_t input_length = 0;
    char *input = read_line(&input_length);
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