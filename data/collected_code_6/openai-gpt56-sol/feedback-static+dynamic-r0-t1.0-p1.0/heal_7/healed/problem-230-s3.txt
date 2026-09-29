#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static char *replace_spaces(const char *source, size_t length, char replacement)
{
    char *result;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
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

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_line(char **buffer, size_t *length)
{
    char *line;
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    line = malloc((size_t)INPUT_SIZE + 1U);
    if (line == NULL) {
        return 0;
    }

    used = 0U;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0U) {
                free(line);
                return 0;
            }
            break;
        }

        if (used >= (size_t)INPUT_SIZE) {
            if (discard_line() == EOF && ferror(stdin)) {
                clearerr(stdin);
            }
            free(line);
            return 0;
        }

        line[used++] = (char)ch;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;

    return 1;
}

int main(void)
{
    char *input;
    char *replacement_line;
    char *result;
    size_t input_length;
    size_t replacement_length;
    char replacement;

    input = NULL;
    replacement_line = NULL;
    result = NULL;

    if (!read_line(&input, &input_length)) {
        fputs("Failed to read the string or input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(&replacement_line, &replacement_length)) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (replacement_length != 1U) {
        fputs("Invalid replacement character.\n", stderr);
        free(replacement_line);
        free(input);
        return EXIT_FAILURE;
    }

    replacement = replacement_line[0];
    free(replacement_line);

    result = replace_spaces(input, input_length, replacement);
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