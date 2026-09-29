#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_present_characters(const char *source, const char *characters)
{
    unsigned char present[UCHAR_MAX + 1] = {0};
    size_t source_length;
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL) {
        return NULL;
    }

    for (const unsigned char *p = (const unsigned char *)characters;
         *p != '\0';
         ++p) {
        present[*p] = 1;
    }

    source_length = strlen(source);

    if (source_length > SIZE_MAX - 1) {
        return NULL;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char current = (unsigned char)source[read_index];

        if (present[current] == 0) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length == capacity) {
        char *new_buffer;

        if (capacity == SIZE_MAX) {
            free(buffer);
            return NULL;
        }

        new_buffer = realloc(buffer, capacity + 1);
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
    char *first = read_line(stdin);
    char *second;
    char *result;

    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_line(stdin);
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    result = remove_present_characters(first, second);
    free(first);
    free(second);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}