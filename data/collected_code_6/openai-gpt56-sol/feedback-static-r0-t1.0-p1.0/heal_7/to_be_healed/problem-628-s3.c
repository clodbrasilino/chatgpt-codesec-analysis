#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *replace_spaces(const char *input, size_t length)
{
    if (input == NULL && length != 0U) {
        return NULL;
    }

    size_t spaces = 0U;

    for (size_t i = 0U; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (length > SIZE_MAX - 1U ||
        spaces > (SIZE_MAX - length - 1U) / 2U) {
        return NULL;
    }

    size_t output_length = length + spaces * 2U;
    char *output = malloc(output_length + 1U);

    if (output == NULL) {
        return NULL;
    }

    size_t destination = 0U;

    for (size_t i = 0U; i < length; ++i) {
        if (input[i] == ' ') {
            output[destination++] = '%';
            output[destination++] = '2';
            output[destination++] = '0';
        } else {
            output[destination++] = input[i];
        }
    }

    output[destination] = '\0';
    return output;
}

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    for (;;) {
        if (fgets(buffer, (int)sizeof buffer, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        int read_failed = ferror(stdin);
        free(input);

        if (read_failed) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        int discard_status = discard_line();
        free(input);

        if (discard_status != 0) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    char *result = replace_spaces(input, length);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}