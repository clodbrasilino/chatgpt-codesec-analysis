#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 1024U

static int read_line(FILE *stream, char **output, size_t *output_length)
{
    char *buffer;
    size_t length = 0U;
    int ch;

    if (stream == NULL || output == NULL || output_length == NULL) {
        return 0;
    }

    *output = NULL;
    *output_length = 0U;

    buffer = malloc((size_t)INPUT_LIMIT + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length == INPUT_LIMIT) {
            do {
                ch = fgetc(stream);
            } while (ch != '\n' && ch != EOF);

            free(buffer);
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 0;
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

    if (source == NULL || length > INPUT_LIMIT || length == SIZE_MAX) {
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

int main(void)
{
    char *input;
    char *result;
    size_t length;
    int replacement;

    if (!read_line(stdin, &input, &length)) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        replacement = fgetc(stdin);
    } while (replacement != EOF && is_input_whitespace(replacement));

    if (replacement == EOF) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    result = replace_spaces(input, length, (char)(unsigned char)replacement);
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