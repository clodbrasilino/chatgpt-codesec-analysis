#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              char character)
{
    size_t output_length = 0;
    size_t i;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            ++output_length;
        }
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    output_length = 0;

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            output[output_length++] = input[i];
        }
    }

    output[output_length] = '\0';
    return output;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return -1;
    }

    if (*capacity >= required) {
        return 0;
    }

    new_capacity = (*capacity == 0) ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *result = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int ch = EOF;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(result);
            return -1;
        }

        if (grow_buffer(&result, &capacity, used + 2) != 0) {
            free(result);
            return -1;
        }

        result[used++] = (char)ch;
    }

    if (ch == EOF && (ferror(stream) || used == 0)) {
        free(result);
        return -1;
    }

    if (grow_buffer(&result, &capacity, used + 1) != 0) {
        free(result);
        return -1;
    }

    result[used] = '\0';
    *buffer = result;
    *length = used;
    return 0;
}

static int read_character(FILE *stream, char *character)
{
    char *line = NULL;
    size_t length = 0;
    int status = -1;

    if (stream == NULL || character == NULL) {
        return -1;
    }

    if (read_line(stream, &line, &length) == 0 && length == 1) {
        *character = line[0];
        status = 0;
    }

    free(line);
    return status;
}

int main(void)
{
    char *input = NULL;
    char *result = NULL;
    char character;
    size_t input_length = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_length) != 0) {
        goto cleanup;
    }

    if (read_character(stdin, &character) != 0) {
        goto cleanup;
    }

    result = remove_character(input, input_length, character);
    if (result == NULL) {
        goto cleanup;
    }

    if (puts(result) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(input);
    return status;
}