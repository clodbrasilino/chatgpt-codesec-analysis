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

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *line;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    for (;;) {
        int input = fgetc(stream);

        if (input == EOF) {
            if (ferror(stream) || used == 0) {
                free(line);
                return 0;
            }
            break;
        }

        if (input == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (used + 1 == capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(line);
                return 0;
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                free(line);
                return 0;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[used++] = (char)(unsigned char)input;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return 1;
}

int main(void)
{
    char *string;
    size_t length;
    int character;
    const char *result;

    if (!read_line(stdin, &string, &length)) {
        return EXIT_FAILURE;
    }

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