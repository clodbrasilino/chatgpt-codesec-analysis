#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

static char *replace_spaces(const char *source, size_t source_size,
                            char replacement)
{
    const char *terminator;
    char *result;
    size_t length;
    size_t i;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
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

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return 0;
    }

    used = 0U;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used + 1U >= capacity) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            buffer[0] = '\0';
            *length = 0U;
            return 0;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && used == 0U) {
        buffer[0] = '\0';
        *length = 0U;
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
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
    char replacement_line[3U];
    char replacement;
    char *result;
    size_t input_length;
    size_t replacement_length;

    if (!read_line(input, sizeof(input), &input_length)) {
        fputs("Failed to read the string or input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(replacement_line, sizeof(replacement_line),
                   &replacement_length)) {
        fputs("Failed to read the replacement character.\n", stderr);
        return EXIT_FAILURE;
    }

    if (replacement_length != 1U) {
        fputs("Invalid replacement character.\n", stderr);
        return EXIT_FAILURE;
    }

    replacement = replacement_line[0];

    result = replace_spaces(input, input_length + 1U, replacement);
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