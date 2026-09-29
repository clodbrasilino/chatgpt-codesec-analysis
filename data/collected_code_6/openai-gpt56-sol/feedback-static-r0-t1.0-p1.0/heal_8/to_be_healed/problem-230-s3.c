#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LIMIT 1024U

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n') {
        if (ch == EOF) {
            return ferror(stream) == 0;
        }
    }

    return 1;
}

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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length >= (size_t)INPUT_LIMIT) {
            if (!discard_line(stream)) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }

        buffer[length] = (char)(unsigned char)ch;
        ++length;
    }

    if (ch == EOF && (ferror(stream) != 0 || length == 0U)) {
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
    int ch;

    if (stream == NULL || replacement == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (!is_input_whitespace(ch)) {
            *replacement = (char)(unsigned char)ch;
            return 1;
        }
    }

    return 0;
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