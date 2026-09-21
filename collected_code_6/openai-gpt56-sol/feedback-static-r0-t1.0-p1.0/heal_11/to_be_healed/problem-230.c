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

static int discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != '\n') {
        if (character == EOF) {
            return ferror(stream) ? -1 : 0;
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

    buffer[0] = '\0';
    *length = 0U;

    while (index + 1U < capacity) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == '\n') {
            buffer[index] = '\0';
            *length = index;
            return 0;
        }

        if (character == EOF) {
            if (ferror(stream) || index == 0U) {
                return -1;
            }

            buffer[index] = '\0';
            *length = index;
            return 0;
        }

        buffer[index++] = (char)character;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stream);

    if (character == '\n') {
        buffer[index] = '\0';
        *length = index;
        return 0;
    }

    if (character == EOF) {
        if (ferror(stream)) {
            buffer[0] = '\0';
            return -1;
        }

        buffer[index] = '\0';
        *length = index;
        return 0;
    }

    if (discard_line(stream) != 0) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';
    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char replacement_buffer[2U];
    size_t length;
    size_t replacement_length;

    if (read_line(stdin, input, sizeof(input), &length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(stdin, replacement_buffer, sizeof(replacement_buffer),
                  &replacement_length) != 0 ||
        replacement_length != 1U ||
        replacement_buffer[0] == '\0') {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, replacement_buffer[0]) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, sizeof(input[0]), length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}