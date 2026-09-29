#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_multiple_spaces(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos = 0;
    size_t write_pos = 0;
    int previous_space = 0;

    if (input == NULL || output == NULL || input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    while (read_pos < input_len) {
        unsigned char current = (unsigned char)input[read_pos++];

        if (current == ' ') {
            if (previous_space) {
                continue;
            }
            previous_space = 1;
        } else {
            previous_space = 0;
        }

        result[write_pos++] = (char)current;
    }

    result[write_pos] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    if (remove_multiple_spaces(input, length, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (fwrite(output, 1, strlen(output), stdout) != strlen(output) ||
        fputc('\n', stdout) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}