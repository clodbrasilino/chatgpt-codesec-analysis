#include <stdio.h>
#include <stdlib.h>

static void remove_character(char *string, int character)
{
    unsigned char *source = (unsigned char *)string;
    unsigned char *destination = (unsigned char *)string;

    while (*source != '\0') {
        if (*source != (unsigned char)character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int input;

    while ((input = fgetc(stream)) != '\n' && input != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)input;
    }

    if (input == EOF && (ferror(stream) || length == 0)) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *string;
    char *character_line;

    string = read_line(stdin);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    character_line = read_line(stdin);
    if (character_line == NULL || character_line[0] == '\0') {
        free(character_line);
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, (unsigned char)character_line[0]);

    if (puts(string) == EOF) {
        free(character_line);
        free(string);
        return EXIT_FAILURE;
    }

    free(character_line);
    free(string);
    return EXIT_SUCCESS;
}