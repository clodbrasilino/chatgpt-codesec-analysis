#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static const char *find_last_char(const char *string, int character)
{
    if (string == NULL) {
        return NULL;
    }

    return strrchr(string, (unsigned char)character);
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *string = malloc(capacity);
    int character;
    const char *result;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t available;
        const char *newline;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;

            if (new_capacity > (size_t)INT_MAX) {
                free(string);
                return EXIT_FAILURE;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        available = capacity - length;
        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(string + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        newline = strchr(string + length, '\n');
        if (newline != NULL) {
            length = (size_t)(newline - string);
            break;
        }

        length += strnlen(string + length, available);

        if (feof(stdin)) {
            break;
        }
    }

    string[length] = '\0';

    character = fgetc(stdin);
    if (character == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    result = find_last_char(string, character);

    if (result == NULL) {
        puts("Character not found");
    } else {
        printf("%td\n", result - string);
    }

    free(string);
    return EXIT_SUCCESS;
}