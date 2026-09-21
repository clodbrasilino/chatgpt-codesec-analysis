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

    read_index = 0U;
    write_index = 0U;

    while (string[read_index] != '\0') {
        if ((read_index & 1U) == 0U) {
            string[write_index++] = string[read_index];
        }
        ++read_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string;
    size_t capacity;
    size_t length;
    int character;

    capacity = 128U;
    length = 0U;
    string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= SIZE_MAX - 1U) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required;
            size_t new_capacity;
            char *resized;

            required = length + 2U;
            new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
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