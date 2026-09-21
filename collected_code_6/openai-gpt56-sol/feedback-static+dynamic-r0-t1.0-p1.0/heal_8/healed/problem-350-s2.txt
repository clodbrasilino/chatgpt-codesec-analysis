#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              unsigned char character)
{
    size_t output_length = 0;
    size_t i;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
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

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            output[output_length++] = input[i];
        }
    }

    output[output_length] = '\0';
    return output;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *line;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        char *resized;

        if (fgets(line + used, (int)(capacity - used), stream) == NULL) {
            if (ferror(stream) || used == 0) {
                free(line);
                return NULL;
            }
            break;
        }

        while (line[used] != '\0' && line[used] != '\n') {
            ++used;
        }

        if (line[used] == '\n') {
            break;
        }

        if (feof(stream)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            free(line);
            return NULL;
        }

        capacity *= 2;
        resized = realloc(line, capacity);
        if (resized == NULL) {
            free(line);
            return NULL;
        }

        line = resized;
    }

    if (used > 0 && line[used - 1] == '\r') {
        --used;
    }

    line[used] = '\0';
    *length = used;

    return line;
}

int main(void)
{
    char *input;
    char *character_line;
    char *result;
    size_t input_length;
    size_t character_length;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    character_line = read_line(stdin, &character_length);
    if (character_line == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (character_length != 1) {
        free(character_line);
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, input_length,
                              (unsigned char)character_line[0]);

    free(character_line);
    free(input);

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