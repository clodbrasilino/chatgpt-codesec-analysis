#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 1024U

static int discard_line(FILE *stream)
{
    if (stream == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            return 1;
        }

        if (ch == EOF) {
            return ferror(stream) == 0;
        }
    }
}

static int read_line(FILE *stream, char **output, size_t *output_length)
{
    char *buffer;
    size_t length = 0U;

    if (stream == NULL || output == NULL || output_length == NULL) {
        return 0;
    }

    *output = NULL;
    *output_length = 0U;

    buffer = malloc((size_t)INPUT_LIMIT + 1U);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length >= (size_t)INPUT_LIMIT) {
            int discarded = discard_line(stream);

            free(buffer);
            return discarded ? 0 : 0;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;

    return 1;
}

static char *replace_spaces(const char *source, size_t length, char replacement)
{
    char *result;
    size_t i;

    if (source == NULL || length > (size_t)INPUT_LIMIT) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = source[i] == ' ' ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

static int is_input_whitespace(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_replacement(FILE *stream, char *replacement)
{
    if (stream == NULL || replacement == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            return 0;
        }

        if (!is_input_whitespace(ch)) {
            *replacement = (char)(unsigned char)ch;
            return 1;
        }
    }
}

int main(void)
{
    char *input = NULL;
    char *result = NULL;
    char replacement;
    size_t length = 0U;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (!read_replacement(stdin, &replacement)) {
        fputs("Failed to read the replacement character.\n", stderr);
        goto cleanup;
    }

    result = replace_spaces(input, length, replacement);
    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
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