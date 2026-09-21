#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        int failed = ferror(stdin);
        free(input);

        if (failed) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    size_t length = 0U;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        free(input);
        fputs("Input is too long.\n", stderr);
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