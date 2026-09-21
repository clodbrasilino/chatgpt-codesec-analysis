#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 1024U

static int discard_line(FILE *stream)
{
    int ch;

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stream);
}

static int read_line(FILE *stream, char **output, size_t *output_length)
{
    char *buffer;
    size_t length = 0U;
    int ch = EOF;

    if (stream == NULL || output == NULL || output_length == NULL) {
        return 0;
    }

    *output = NULL;
    *output_length = 0U;

    buffer = malloc((size_t)INPUT_LIMIT + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while (length < (size_t)INPUT_LIMIT) {
        ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length == (size_t)INPUT_LIMIT) {
        ch = fgetc(stream);

        if (ch != '\n' && ch != EOF) {
            if (!discard_line(stream)) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }
    }

    if (ch == EOF && (ferror(stream) || length == 0U)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;
    return 1;
}

static char *replace_spaces(const char *source, size_t length,
                            char replacement)
{
    char *result;
    size_t i;

    if (source == NULL || length > (size_t)INPUT_LIMIT ||
        length == SIZE_MAX) {
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
    int ch;

    if (stream == NULL || replacement == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && is_input_whitespace(ch));

    if (ch == EOF) {
        return 0;
    }

    *replacement = (char)(unsigned char)ch;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *result = NULL;
    char replacement;
    size_t length = 0U;

    if (!read_line(stdin, &input, &length)) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_replacement(stdin, &replacement)) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    result = replace_spaces(input, length, replacement);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}