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
    char *input;
    size_t length = 0;
    size_t capacity = 128;
    int status = EXIT_FAILURE;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length >= SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = length + 2;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                goto cleanup;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
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