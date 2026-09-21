#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int replace_spaces(const char *input, size_t input_length, char **output)
{
    size_t spaces = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;
    char *result;

    if (output == NULL || (input == NULL && input_length != 0)) {
        return -1;
    }

    *output = NULL;

    for (i = 0; i < input_length; ++i) {
        if (input[i] == ' ') {
            if (spaces == SIZE_MAX) {
                return -1;
            }
            ++spaces;
        }
    }

    if (input_length > SIZE_MAX - 1 ||
        spaces > (SIZE_MAX - input_length - 1) / 2) {
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
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                goto cleanup;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        goto cleanup;
    }

    if (replace_spaces(input, length, &output) != 0) {
        goto cleanup;
    }

    if (puts(output) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}