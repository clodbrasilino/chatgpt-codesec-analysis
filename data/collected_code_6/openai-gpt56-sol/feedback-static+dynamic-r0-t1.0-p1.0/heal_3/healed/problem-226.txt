#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_indices(char *string)
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
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required;

        if (length > SIZE_MAX - 2) {
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    remove_odd_indices(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}