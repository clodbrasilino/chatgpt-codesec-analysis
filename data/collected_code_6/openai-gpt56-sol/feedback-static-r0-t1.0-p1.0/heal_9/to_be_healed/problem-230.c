#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

static int read_line(FILE *stream, char *buffer, size_t capacity, size_t *length)
{
    size_t index = 0U;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        if (index + 1U >= capacity) {
            if (discard_line(stream) != 0) {
                return -1;
            }
            return -1;
        }

        buffer[index++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && index == 0U)) {
        return -1;
    }

    buffer[index] = '\0';
    *length = index;
    return 0;
}

int main(void)
{
    char *input;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char replacement_buffer[2];
    size_t length;
    size_t replacement_length;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (read_line(stdin, input, INPUT_SIZE, &length) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (read_line(stdin, replacement_buffer, sizeof(replacement_buffer),
                  &replacement_length) != 0 ||
        replacement_length != 1U ||
        replacement_buffer[0] == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, replacement_buffer[0]) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}