#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              unsigned char character)
{
    size_t output_length = 0;
    size_t index;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (index = 0; index < input_length; ++index) {
        if ((unsigned char)input[index] != character) {
            if (output_length == SIZE_MAX - 1) {
                return NULL;
            }
            ++output_length;
        }
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    output_length = 0;

    for (index = 0; index < input_length; ++index) {
        if ((unsigned char)input[index] != character) {
            output[output_length++] = input[index];
        }
    }

    output[output_length] = '\0';
    return output;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (used == capacity - 1) {
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

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *length = used;

    return buffer;
}

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    char *result = NULL;
    size_t input_length = 0;
    size_t character_line_length = 0;
    int status = EXIT_FAILURE;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        goto cleanup;
    }

    character_line = read_line(stdin, &character_line_length);
    if (character_line == NULL || character_line_length == 0) {
        goto cleanup;
    }

    result = remove_character(input, input_length,
                              (unsigned char)character_line[0]);
    if (result == NULL) {
        goto cleanup;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(character_line);
    free(input);

    return status;
}