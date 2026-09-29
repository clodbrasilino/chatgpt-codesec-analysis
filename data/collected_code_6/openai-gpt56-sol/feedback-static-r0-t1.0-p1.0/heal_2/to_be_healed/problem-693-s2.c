#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(char *string, size_t capacity)
{
    size_t read_pos;
    size_t write_pos;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    for (read_pos = 0; read_pos < capacity; ++read_pos) {
        if (string[read_pos] == '\0') {
            break;
        }
    }

    if (read_pos == capacity) {
        return -1;
    }

    read_pos = 0;
    write_pos = 0;

    while (string[read_pos] != '\0') {
        if (string[read_pos] == ' ' && string[read_pos + 1] == ' ') {
            string[write_pos++] = ' ';

            while (string[read_pos] == ' ') {
                ++read_pos;
            }
        } else {
            string[write_pos++] = string[read_pos++];
        }
    }

    string[write_pos] = '\0';
    return 0;
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
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

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(string);
        return EXIT_SUCCESS;
    }

    string[length] = '\0';

    if (remove_multiple_spaces(string, capacity) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}