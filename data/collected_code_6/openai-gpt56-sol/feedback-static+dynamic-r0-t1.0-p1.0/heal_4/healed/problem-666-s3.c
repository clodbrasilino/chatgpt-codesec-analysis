#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t count_char_occurrences(const char *string, unsigned char target)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if ((unsigned char)*string == target) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int current;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        current = fgetc(stdin);

        if (current == EOF || current == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)current;
    }

    if (current == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (current == EOF && length == 0) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    character = fgetc(stdin);
    if (character == EOF) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n",
           count_char_occurrences(input, (unsigned char)character));

    free(input);
    return EXIT_SUCCESS;
}