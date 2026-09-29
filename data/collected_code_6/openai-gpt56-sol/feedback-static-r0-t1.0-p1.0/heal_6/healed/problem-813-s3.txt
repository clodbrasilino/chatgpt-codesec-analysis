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
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        size_t required;

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *new_buffer;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)character;
        ++length;
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (length >= capacity) {
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[length] = '\0';

    if (printf("%zu\n", string_length(buffer)) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}