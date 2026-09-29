#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_indices(char *string)
{
    size_t read_index = 0;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];

        if (string[read_index + 1] == '\0') {
            break;
        }

        read_index += 2;
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
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
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

        string[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
    }

    string[length] = '\0';
    remove_odd_indices(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}