#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(char *string, size_t capacity)
{
    size_t read_pos;
    size_t write_pos = 0;
    int previous_was_space = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    for (read_pos = 0; read_pos < capacity; ++read_pos) {
        char current = string[read_pos];

        if (current == '\0') {
            string[write_pos] = '\0';
            return 0;
        }

        if (current != ' ' || !previous_was_space) {
            string[write_pos++] = current;
        }

        previous_was_space = (current == ' ');
    }

    return -1;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_string;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_string = realloc(string, new_capacity);

            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    string[length] = '\0';

    if (remove_multiple_spaces(string, capacity) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}