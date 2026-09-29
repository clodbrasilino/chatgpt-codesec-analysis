#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_multiple_spaces(char *str)
{
    char *read_ptr = str;
    char *write_ptr = str;
    int previous_was_space = 0;

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ' || !previous_was_space) {
            *write_ptr++ = *read_ptr;
        }

        previous_was_space = (*read_ptr == ' ');
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(input + length, (int)(capacity - length), stdin) != NULL) {
        char *newline = NULL;

        for (size_t i = length; input[i] != '\0'; ++i) {
            if (input[i] == '\n') {
                newline = &input[i];
                break;
            }
        }

        if (newline != NULL) {
            *newline = '\0';
            length = (size_t)(newline - input);
            break;
        }

        while (input[length] != '\0') {
            ++length;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            goto cleanup;
        }

        size_t new_capacity = capacity * 2;
        if (new_capacity > (size_t)INT32_MAX) {
            new_capacity = (size_t)INT32_MAX;
        }

        if (new_capacity <= capacity) {
            goto cleanup;
        }

        char *temporary = realloc(input, new_capacity);
        if (temporary == NULL) {
            goto cleanup;
        }

        input = temporary;
        capacity = new_capacity;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    input[length] = '\0';
    remove_multiple_spaces(input);

    if (puts(input) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}