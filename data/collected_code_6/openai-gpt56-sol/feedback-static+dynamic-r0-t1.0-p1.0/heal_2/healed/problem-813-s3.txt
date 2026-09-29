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
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = length + 2;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                new_capacity = length + 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (buffer == NULL) {
        buffer = malloc(1);

        if (buffer == NULL) {
            return EXIT_FAILURE;
        }
    }

    buffer[length] = '\0';

    printf("%zu\n", string_length(buffer));

    free(buffer);
    return EXIT_SUCCESS;
}