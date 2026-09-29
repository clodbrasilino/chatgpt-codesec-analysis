#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        unsigned char character;
        size_t bytes_read = fread(&character, 1, 1, stream);

        if (bytes_read == 0) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

static size_t minimize_string(char *string)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest_frequency = 0;
    size_t read_index;
    size_t write_index = 0;
    unsigned char character_to_remove = 0;

    if (string == NULL) {
        return 0;
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];

        ++frequencies[character];

        if (frequencies[character] > highest_frequency) {
            highest_frequency = frequencies[character];
            character_to_remove = character;
        }
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];

        if (character != character_to_remove) {
            string[write_index++] = string[read_index];
        }
    }

    string[write_index] = '\0';
    return write_index;
}

int main(void)
{
    char *string = read_line(stdin);
    size_t minimized_length;

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    minimized_length = minimize_string(string);

    if (printf("%zu\n", minimized_length) < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}