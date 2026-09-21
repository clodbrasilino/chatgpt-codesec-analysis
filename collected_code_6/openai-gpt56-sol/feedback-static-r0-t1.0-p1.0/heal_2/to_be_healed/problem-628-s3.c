#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *replace_spaces(const char *input, size_t length)
{
    size_t spaces = 0;

    if (input == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - length - 1U) / 2U) {
        return NULL;
    }

    size_t output_length = length + spaces * 2U;
    char *output = malloc(output_length + 1U);

    if (output == NULL) {
        return NULL;
    }

    char *destination = output;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ' ') {
            *destination++ = '%';
            *destination++ = '2';
            *destination++ = '0';
        } else {
            *destination++ = input[i];
        }
    }

    *destination = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == SIZE_MAX - 1U) {
            free(input);
            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    fprintf(stderr, "Input is too long.\n");
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    char *result = replace_spaces(input, length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to replace spaces.\n");
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}