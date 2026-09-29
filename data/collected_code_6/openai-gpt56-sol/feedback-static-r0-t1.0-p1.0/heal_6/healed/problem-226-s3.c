#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_odd_indices(char *string)
{
    size_t read_index;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    for (read_index = 0U; string[read_index] != '\0'; read_index += 2U) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int status = EXIT_FAILURE;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                new_capacity = length + 2U;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (string == NULL) {
        string = malloc(1U);
        if (string == NULL) {
            goto cleanup;
        }
        capacity = 1U;
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