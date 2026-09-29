#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_characters(char *string)
{
    size_t read_index = 0;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        if ((read_index % 2U) == 0U) {
            string[write_index++] = string[read_index];
        }
        ++read_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;

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

            char *resized = realloc(string, new_capacity);
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

    if (string == NULL) {
        string = malloc(1U);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
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