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
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        char *result;

        if (capacity - length < 2) {
            size_t new_capacity;
            char *new_string;

            if (capacity > SIZE_MAX / 2) {
                if (capacity == SIZE_MAX) {
                    free(string);
                    return EXIT_FAILURE;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        result = fgets(string + length, (int)(capacity - length), stdin);

        if (result == NULL) {
            if (ferror(stdin)) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        while (string[length] != '\0' && string[length] != '\n') {
            ++length;
        }

        if (string[length] == '\n') {
            /* Possible weaknesses found:
             *  string[length] is assigned
             */
            string[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    /* Possible weaknesses found:
     *  Variable 'string[length]' is reassigned a value before the old one has been used. [redundantAssignment]
     *  string[length] is overwritten
     */
    string[length] = '\0';

    if (remove_multiple_spaces(string, length + 1) != 0) {
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