#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int remove_multiple_spaces(char *string, size_t capacity)
{
    size_t read_pos = 0;
    size_t write_pos = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (read_pos < capacity && string[read_pos] != '\0') {
        if (string[read_pos] != ' ' ||
            (write_pos > 0 && string[write_pos - 1] != ' ')) {
            string[write_pos++] = string[read_pos];
        }
        ++read_pos;
    }

    if (read_pos == capacity) {
        return -1;
    }

    string[write_pos] = '\0';
    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_string;

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

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
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