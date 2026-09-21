#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_character(char *string, unsigned char target)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

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
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
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

        if (length == capacity - 1) {
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

static int read_character_line(FILE *stream, unsigned char *character)
{
    char buffer[2];
    int ch;

    if (stream == NULL || character == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stream) == NULL) {
        return 0;
    }

    if (buffer[0] == '\n') {
        *character = (unsigned char)'\n';
        return 1;
    }

    *character = (unsigned char)buffer[0];

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch != EOF || !ferror(stream);
}

int main(void)
{
    char *string;
    unsigned char character;

    string = read_line(stdin);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_character_line(stdin, &character)) {
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