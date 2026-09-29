#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_odd_indices(char *string)
{
    size_t read_index = 0U;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];

        if (string[read_index + 1U] == '\0') {
            break;
        }

        read_index += 2U;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int status = EXIT_FAILURE;

    for (;;) {
        char input_buffer[4096];
        size_t input_length;
        size_t required;
        char *resized;

        if (fgets(input_buffer, sizeof input_buffer, stdin) == NULL) {
            if (ferror(stdin) || length == 0U) {
                goto cleanup;
            }
            break;
        }

        input_length = 0U;
        while (input_length < sizeof input_buffer &&
               input_buffer[input_length] != '\0' &&
               input_buffer[input_length] != '\n') {
            ++input_length;
        }

        if (input_length > SIZE_MAX - length - 1U) {
            goto cleanup;
        }

        required = length + input_length + 1U;
        if (required > capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            string = resized;
            capacity = new_capacity;
        }

        for (size_t index = 0U; index < input_length; ++index) {
            string[length + index] = input_buffer[index];
        }
        length += input_length;

        if (input_buffer[input_length] == '\n') {
            break;
        }
    }

    if (string == NULL) {
        string = malloc(1U);
        if (string == NULL) {
            goto cleanup;
        }
    }

    string[length] = '\0';
    remove_odd_indices(string);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(string);
    return status;
}