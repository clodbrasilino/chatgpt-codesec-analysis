#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U
#define DISCARD_SIZE 256U

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[DISCARD_SIZE];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i;

        for (i = 0U; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return 1;
            }
        }
    }

    return ferror(stdin) == 0;
}

static int read_line(char **buffer, size_t *length)
{
    char *line;
    size_t used = 0U;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    line = malloc((size_t)INPUT_SIZE + 1U);
    if (line == NULL) {
        return 0;
    }

    while (used < (size_t)INPUT_SIZE) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            line[used] = '\0';
            *buffer = line;
            *length = used;
            return 1;
        }

        if (ch == EOF) {
            if (ferror(stdin) != 0 || used == 0U) {
                free(line);
                return 0;
            }

            line[used] = '\0';
            *buffer = line;
            *length = used;
            return 1;
        }

        line[used++] = (char)ch;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || (ch == EOF && ferror(stdin) == 0)) {
            line[used] = '\0';
            *buffer = line;
            *length = used;
            return 1;
        }

        if (ch != EOF) {
            (void)discard_line();
        }
    }

    free(line);
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *replacement_line = NULL;
    char *result;
    size_t input_length = 0U;
    size_t replacement_length = 0U;
    char replacement;

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