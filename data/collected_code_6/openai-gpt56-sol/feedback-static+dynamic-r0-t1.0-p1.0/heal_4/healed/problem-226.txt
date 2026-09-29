#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_indices(char *string)
{
    size_t read_index;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    for (read_index = 0; string[read_index] != '\0'; read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *input;
    size_t capacity = 128;
    size_t length = 0;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = length + 2;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
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

    input[length] = '\0';
    remove_odd_indices(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}