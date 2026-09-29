#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_multiple_spaces(char *string, size_t length)
{
    size_t read_pos;
    size_t write_pos = 0;
    int previous_was_space = 0;

    if (string == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < length; ++read_pos) {
        char current = string[read_pos];

        if (current != ' ' || !previous_was_space) {
            string[write_pos++] = current;
        }

        previous_was_space = (current == ' ');
    }

    string[write_pos] = '\0';
    return 0;
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

        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_string;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(string);
                return EXIT_FAILURE;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    string[length] = '\0';

    if (remove_multiple_spaces(string, length) != 0) {
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