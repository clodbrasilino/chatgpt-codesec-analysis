#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_present_characters(const char *source, const char *characters)
{
    unsigned char present[UINT8_MAX + 1] = {0};
    size_t source_length = 0;
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

    for (const char *p = source; *p != '\0'; ++p) {
        if (source_length == SIZE_MAX - 1) {
            return NULL;
        }
        ++source_length;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char ch = (unsigned char)source[read_index];

        if (present[ch] == 0) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t required;
            size_t new_capacity;
            char *new_line;

            if (length > SIZE_MAX - 2) {
                free(line);
                return NULL;
            }

            required = length + 2;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return NULL;
            }

            line = new_line;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        line[length++] = (char)ch;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *first;
    char *second;
    char *result;

    first = read_line(stdin);
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