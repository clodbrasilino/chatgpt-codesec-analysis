#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(char *string, size_t capacity)
{
    size_t read_pos = 0;
    size_t write_pos = 0;
    int previous_was_space = 0;

    if (string == NULL || capacity == 0) {
        return -1;
    }

    while (read_pos < capacity && string[read_pos] != '\0') {
        ++read_pos;
    }

    if (read_pos == capacity) {
        return -1;
    }

    read_pos = 0;

    while (string[read_pos] != '\0') {
        if (string[read_pos] != ' ' || !previous_was_space) {
            string[write_pos++] = string[read_pos];
        }

        previous_was_space = string[read_pos] == ' ';
        ++read_pos;
    }

    string[write_pos] = '\0';
    return 0;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);
    int character;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
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

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(string);
        return EXIT_SUCCESS;
    }

    string[length] = '\0';

    if (remove_multiple_spaces(string, length + 1) != 0) {
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