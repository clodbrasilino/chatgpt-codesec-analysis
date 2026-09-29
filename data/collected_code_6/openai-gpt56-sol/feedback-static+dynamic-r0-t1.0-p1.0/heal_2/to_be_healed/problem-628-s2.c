#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int replace_spaces(const char *input, size_t input_length, char **output)
{
    size_t spaces = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (i = 0; i < input_length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (spaces > (SIZE_MAX - input_length - 1) / 2) {
        return -1;
    }

    output_length = input_length + spaces * 2;
    result = malloc(output_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *temporary;

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (length >= capacity) {
        char *temporary = realloc(input, length + 1);
        if (temporary == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = temporary;
    }

    input[length] = '\0';

    if (replace_spaces(input, length, &output) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}