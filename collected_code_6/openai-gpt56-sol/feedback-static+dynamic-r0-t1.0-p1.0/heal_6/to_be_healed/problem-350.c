#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static char *remove_character(const char *input, size_t input_length,
                              char character)
{
    char *output;
    size_t read_index;
    size_t write_index = 0U;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0U; read_index < input_length; ++read_index) {
        if (input[read_index] != character) {
            output[write_index++] = input[read_index];
        }
    }

    output[write_index] = '\0';
    return output;
}

static int discard_line_remainder(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return !ferror(stdin);
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t index = 0U;
    int ch;

    if (buffer == NULL || length == NULL || capacity < 2U) {
        return 0;
    }

    buffer[0] = '\0';
    *length = 0U;

    while (index < capacity - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || index == 0U) {
                return 0;
            }
            break;
        }

        buffer[index++] = (char)ch;
    }

    if (index == capacity - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (!discard_line_remainder()) {
                return 0;
            }
            buffer[0] = '\0';
            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            buffer[0] = '\0';
            return 0;
        }
    }

    if (index > 0U && buffer[index - 1U] == '\r') {
        --index;
    }

    buffer[index] = '\0';
    *length = index;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    char *result = NULL;
    size_t input_length = 0U;
    size_t character_length = 0U;
    int status = EXIT_FAILURE;

    input = malloc(INPUT_CAPACITY);
    character_line = malloc(INPUT_CAPACITY);

    if (input == NULL || character_line == NULL) {
        goto cleanup;
    }

    if (!read_line(input, INPUT_CAPACITY, &input_length)) {
        goto cleanup;
    }

    if (!read_line(character_line, INPUT_CAPACITY, &character_length) ||
        character_length == 0U) {
        goto cleanup;
    }

    result = remove_character(input, input_length, character_line[0]);
    if (result == NULL) {
        goto cleanup;
    }

    if (printf("%s\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    free(character_line);
    free(input);
    return status;
}