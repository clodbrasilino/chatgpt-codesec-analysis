#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int discard_line(void)
{
    int ch = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    char *newline;
    size_t used;

    if (buffer == NULL || length == NULL || capacity < 2U ||
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';
    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        *length = (size_t)(newline - buffer);
        return 0;
    }

    used = strnlen(buffer, capacity);
    if (used >= capacity) {
        buffer[0] = '\0';
        return -1;
    }

    if (used == capacity - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                buffer[0] = '\0';
                return -1;
            }

            buffer[0] = '\0';
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            buffer[0] = '\0';
            return -1;
        }
    }

    *length = used;
    return 0;
}

static int read_replacement(char *replacement)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[3];
    size_t length;

    if (replacement == NULL) {
        return -1;
    }

    if (read_line(line, sizeof(line), &length) != 0 ||
        length != 1U || line[0] == '\0') {
        return -1;
    }

    *replacement = line[0];
    return 0;
}

int main(void)
{
    char *input;
    char replacement;
    size_t length;
    int status = EXIT_FAILURE;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (read_line(input, INPUT_SIZE, &length) != 0) {
        goto cleanup;
    }

    if (read_replacement(&replacement) != 0) {
        goto cleanup;
    }

    if (replace_spaces(input, length, replacement) != 0) {
        goto cleanup;
    }

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}