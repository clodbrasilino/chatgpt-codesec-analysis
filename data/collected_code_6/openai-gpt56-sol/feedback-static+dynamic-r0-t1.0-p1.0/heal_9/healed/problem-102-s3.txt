#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *snake_to_camel(const char *snake)
{
    const unsigned char *source;
    size_t output_length = 0;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source != (unsigned char)'_') {
            if (output_length == SIZE_MAX - 1) {
                return NULL;
            }
            ++output_length;
        }
        ++source;
    }

    camel = malloc(output_length + 1);
    if (camel == NULL) {
        return NULL;
    }

    source = (const unsigned char *)snake;

    while (*source != '\0') {
        if (*source == (unsigned char)'_') {
            capitalize_next = 1;
        } else {
            camel[destination_index++] = capitalize_next
                ? (char)toupper((int)*source)
                : (char)*source;
            capitalize_next = 0;
        }
        ++source;
    }

    camel[destination_index] = '\0';
    return camel;
}

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
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return NULL;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char *argv[])
{
    const char *snake;
    char *input = NULL;
    char *camel;

    if (argc == 2) {
        snake = argv[1];
    } else if (argc == 1) {
        input = read_line(stdin);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        snake = input;
    } else {
        return EXIT_FAILURE;
    }

    camel = snake_to_camel(snake);
    free(input);

    if (camel == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(camel) == EOF) {
        free(camel);
        return EXIT_FAILURE;
    }

    free(camel);
    return EXIT_SUCCESS;
}