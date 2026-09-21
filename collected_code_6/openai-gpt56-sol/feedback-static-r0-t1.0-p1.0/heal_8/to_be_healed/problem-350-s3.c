#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_character(const char *input, size_t input_length,
                              unsigned char character)
{
    size_t output_length = 0;
    size_t i;
    size_t j = 0;
    char *output;

    if (input == NULL && input_length != 0) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if ((unsigned char)input[i] != character) {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
    return output;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

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

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int is_space_character(int character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 0;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (*length == SIZE_MAX) {
            free(*buffer);
            *buffer = NULL;
            return 0;
        }

        if (*length == capacity &&
            !grow_buffer(buffer, &capacity, *length + 1)) {
            free(*buffer);
            *buffer = NULL;
            return 0;
        }

        (*buffer)[(*length)++] = (char)(unsigned char)character;
    }

    if (ferror(stream) || (character == EOF && *length == 0)) {
        free(*buffer);
        *buffer = NULL;
        *length = 0;
        return 0;
    }

    return 1;
}

static int read_nonspace_character(FILE *stream, unsigned char *result)
{
    int character;

    if (stream == NULL || result == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
        if (character == EOF) {
            return 0;
        }
    } while (is_space_character(character));

    *result = (unsigned char)character;
    return 1;
}

int main(void)
{
    char *input;
    char *result;
    size_t input_length;
    unsigned char character;

    if (!read_line(stdin, &input, &input_length)) {
        return EXIT_FAILURE;
    }

    if (!read_nonspace_character(stdin, &character)) {
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, input_length, character);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}