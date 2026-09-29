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
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        char *resized_string;

        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
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

    if (string == NULL) {
        string = malloc(1);
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