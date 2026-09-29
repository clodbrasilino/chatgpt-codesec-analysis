#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 4096

static char *remove_character(const char *input, size_t input_length,
                              char character)
{
    char *output;
    size_t read_index;
    size_t write_index = 0;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        if (input[read_index] != character) {
            output[write_index++] = input[read_index];
        }
    }

    output[write_index] = '\0';
    return output;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch;
}

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    char *result = NULL;
    size_t input_length;
    int status = EXIT_FAILURE;

    input = malloc(INPUT_CAPACITY);
    character_line = malloc(INPUT_CAPACITY);

    if (input == NULL || character_line == NULL) {
        goto cleanup;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[--input_length] = '\0';
    } else if (discard_line() == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (fgets(character_line, INPUT_CAPACITY, stdin) == NULL ||
        character_line[0] == '\0' || character_line[0] == '\n') {
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