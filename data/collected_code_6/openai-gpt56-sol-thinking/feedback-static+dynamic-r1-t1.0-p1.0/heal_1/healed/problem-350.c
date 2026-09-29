#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

static int read_line(FILE *stream, char **result)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int newline_found = 0;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        unsigned char character;
        size_t count = fread(&character, sizeof(character), 1, stream);

        if (count != 1) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            newline_found = 1;
            break;
        }

        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (newline_found && length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *result = buffer;

    return 0;
}

static size_t minimize_string(char *string)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t maximum = 0;
    size_t read_index;
    size_t write_index = 0;
    unsigned char character_to_remove = 0;

    if (string == NULL || string[0] == '\0') {
        return 0;
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        unsigned char character = (unsigned char)string[read_index];

        ++frequencies[character];

        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
            character_to_remove = character;
        }
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        if ((unsigned char)string[read_index] != character_to_remove) {
            string[write_index++] = string[read_index];
        }
    }

    string[write_index] = '\0';
    return write_index;
}

int main(void)
{
    char *string = NULL;
    size_t length;
    int status = EXIT_SUCCESS;

    if (read_line(stdin, &string) != 0) {
        return EXIT_FAILURE;
    }

    length = minimize_string(string);

    if (fwrite(string, sizeof(*string), length, stdout) != length ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(string);
    return status;
}