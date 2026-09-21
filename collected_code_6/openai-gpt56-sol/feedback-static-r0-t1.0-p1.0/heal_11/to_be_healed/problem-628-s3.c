#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH ((size_t)1024U * 1024U)
#define INPUT_CAPACITY (MAX_INPUT_LENGTH + 2U)

static char *replace_spaces(const char *input, size_t length)
{
    size_t spaces = 0U;
    size_t output_length;
    size_t destination = 0U;
    char *output;

    if (input == NULL && length != 0U) {
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (length > SIZE_MAX - 1U ||
        spaces > (SIZE_MAX - length - 1U) / 2U) {
        return NULL;
    }

    output_length = length + spaces * 2U;
    output = malloc(output_length + 1U);

    if (output == NULL) {
        return NULL;
    }

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
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n') {
        if (character == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }

    return 0;
}

int main(void)
{
    char *input;
    char *result;
    size_t length;

    input = malloc(INPUT_CAPACITY);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_CAPACITY, stdin) == NULL) {
        int read_failed = ferror(stdin);
        free(input);

        if (read_failed) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int discard_status = discard_line();
        free(input);

        if (discard_status < 0) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    result = replace_spaces(input, length);
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