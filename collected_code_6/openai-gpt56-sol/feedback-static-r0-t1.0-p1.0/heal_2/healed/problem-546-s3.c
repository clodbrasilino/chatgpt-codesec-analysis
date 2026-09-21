#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const char *find_last_char(const char *str, int ch)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)ch;

    if (str == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*str == target) {
            last = str;
        }
    } while (*str++ != '\0');

    return last;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int current;
    int ch;
    const char *result;

    while ((current = getchar()) != '\n' && current != EOF) {
        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 2 > capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

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

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)current;
    }

    if (current == EOF && length == 0) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX - 2) {
        free(input);
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (capacity < length + 2) {
        char *new_input = realloc(input, length + 2);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length++] = '\n';
    input[length] = '\0';

    ch = getchar();
    if (ch == EOF) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_last_char(input, ch);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    free(input);
    return EXIT_SUCCESS;
}