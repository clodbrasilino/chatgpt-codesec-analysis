#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_characters(char *string)
{
    size_t read_index;
    size_t write_index;

    if (string == NULL) {
        return;
    }

    for (read_index = 0, write_index = 0;
         string[read_index] != '\0';
         read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (capacity <= length + 1) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized_string;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized_string = realloc(string, new_capacity);
            if (resized_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized_string;
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

    if (capacity <= length) {
        char *resized_string;

        if (length == SIZE_MAX) {
            free(string);
            return EXIT_FAILURE;
        }

        resized_string = realloc(string, length + 1);
        if (resized_string == NULL) {
            free(string);
            return EXIT_FAILURE;
        }

        string = resized_string;
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