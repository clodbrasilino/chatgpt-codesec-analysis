#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const char *find_last_char(const char *string, int character)
{
    if (string == NULL) {
        return NULL;
    }

    return strrchr(string, (unsigned char)character);
}

int main(void)
{
    char *string;
    size_t capacity = 128;
    size_t length = 0;
    int character;
    const char *result;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(string + length, (int)(capacity - length), stdin) != NULL) {
        char *newline = strchr(string + length, '\n');

        if (newline != NULL) {
            length = (size_t)(newline - string);
            break;
        }

        length += strlen(string + length);

        if (feof(stdin)) {
            free(string);
            return EXIT_FAILURE;
        }

        if (capacity > SIZE_MAX / 2) {
            free(string);
            return EXIT_FAILURE;
        }

        {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity > (size_t)INT32_MAX) {
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
    }

    if (ferror(stdin) || length == 0 && feof(stdin)) {
        free(string);
        return EXIT_FAILURE;
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