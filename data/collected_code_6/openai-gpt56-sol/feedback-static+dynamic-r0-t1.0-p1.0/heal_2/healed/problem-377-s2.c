#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_character(char *string, int character)
{
    unsigned char target = (unsigned char)character;
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if ((unsigned char)*source != target) {
            *destination++ = *source;
        }
        source++;
    }

    *destination = '\0';
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *string = read_line(stdin);
    int character;
    int input;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    character = fgetc(stdin);
    if (character == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    do {
        input = fgetc(stdin);
    } while (input != '\n' && input != EOF);

    if (input == EOF && ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, character);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}