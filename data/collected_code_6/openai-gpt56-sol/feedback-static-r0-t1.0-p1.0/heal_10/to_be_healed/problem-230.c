#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    size_t i;

    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int read_line(FILE *stream, char *buffer, size_t capacity,
                     size_t *length)
{
    size_t index = 0U;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL || capacity < 2U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        if (index >= capacity - 1U) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stream);
            } while (character != '\n' && character != EOF);

            buffer[0] = '\0';
            *length = 0U;
            return -1;
        }

        buffer[index++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && index == 0U)) {
        buffer[0] = '\0';
        *length = 0U;
        return -1;
    }

    buffer[index] = '\0';
    *length = index;
    return 0;
}

int main(void)
{
    char *input;
    char *replacement_buffer;
    size_t length;
    size_t replacement_length;
    int result = EXIT_FAILURE;

    input = malloc(INPUT_SIZE);
    replacement_buffer = malloc(2U);

    if (input == NULL || replacement_buffer == NULL) {
        goto cleanup;
    }

    if (read_line(stdin, input, INPUT_SIZE, &length) != 0) {
        goto cleanup;
    }

    if (read_line(stdin, replacement_buffer, 2U, &replacement_length) != 0 ||
        replacement_length != 1U ||
        replacement_buffer[0] == '\0') {
        goto cleanup;
    }

    if (replace_spaces(input, length, replacement_buffer[0]) != 0) {
        goto cleanup;
    }

    if (fwrite(input, sizeof(*input), length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(replacement_buffer);
    free(input);
    return result;
}