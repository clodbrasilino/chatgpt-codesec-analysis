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
    int character;
    int status = EXIT_FAILURE;

    while ((character = getchar()) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity = capacity == 0U ? 128U : capacity;
            char *resized;

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

        string[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        goto cleanup;
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