#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_characters(char *string)
{
    char *read_ptr;
    char *write_ptr;

    if (string == NULL) {
        return;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        *write_ptr++ = *read_ptr++;

        if (*read_ptr != '\0') {
            ++read_ptr;
        }
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length == 0U && character == EOF) {
        free(string);
        return EXIT_SUCCESS;
    }

    if (capacity <= length) {
        char *resized = realloc(string, length + 1U);

        if (resized == NULL) {
            free(string);
            return EXIT_FAILURE;
        }

        string = resized;
    }

    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}