#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static const char *find_last_char(const char *string, int character)
{
    const unsigned char target = (unsigned char)character;
    const char *last = NULL;

    if (string == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*string == target) {
            last = string;
        }
    } while (*string++ != '\0');

    return last;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 128;
    char *line = malloc(capacity);
    int input;

    if (line == NULL) {
        return 0;
    }

    *length = 0;

    while ((input = getchar()) != '\n' && input != EOF) {
        if (*length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (*length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = *length + 2;
            } else {
                new_capacity = capacity * 2;
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                return 0;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[(*length)++] = (char)(unsigned char)input;
    }

    if (input == EOF && *length == 0) {
        free(line);
        return 0;
    }

    line[*length] = '\0';
    *buffer = line;
    return 1;
}

int main(void)
{
    char *string;
    size_t length;
    int character;
    const char *result;

    if (!read_line(&string, &length)) {
        return EXIT_FAILURE;
    }

    character = getchar();
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