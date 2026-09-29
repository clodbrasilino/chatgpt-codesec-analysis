#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t string_length(const char *string)
{
    const char *current;

    if (string == NULL) {
        return 0;
    }

    current = string;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - string);
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_buffer;

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

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return EXIT_FAILURE;
        }

        buffer = new_buffer;
        capacity = length + 1;
    }

    buffer[length] = '\0';

    printf("%zu\n", string_length(buffer));

    free(buffer);
    return EXIT_SUCCESS;
}