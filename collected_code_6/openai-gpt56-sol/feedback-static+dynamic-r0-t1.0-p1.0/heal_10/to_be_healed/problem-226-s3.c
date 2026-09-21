#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_indices(char *string)
{
    size_t read_index;
    size_t write_index;

    if (string == NULL) {
        return;
    }

    read_index = 0;
    write_index = 0;

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];
        ++read_index;

        if (string[read_index] != '\0') {
            ++read_index;
        }
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(string);
                return EXIT_FAILURE;
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

    if (ferror(stdin) || (character == EOF && length == 0)) {
        free(string);
        return EXIT_FAILURE;
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