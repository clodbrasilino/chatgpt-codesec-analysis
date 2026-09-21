#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              char character)
{
    size_t index;
    size_t output_length = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (index = 0; index < input_length; ++index) {
        if (input[index] != character) {
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
        if (input[index] != character) {
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
    int ch = EOF;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used >= capacity - 1) {
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

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && (ferror(stream) || used == 0)) {
        free(buffer);
        return NULL;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *input;
    char *character_line;
    char *result;
    size_t input_length;
    size_t character_line_length;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    character_line = read_line(stdin, &character_line_length);
    if (character_line == NULL || character_line_length == 0) {
        free(character_line);
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, input_length, character_line[0]);

    free(character_line);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}