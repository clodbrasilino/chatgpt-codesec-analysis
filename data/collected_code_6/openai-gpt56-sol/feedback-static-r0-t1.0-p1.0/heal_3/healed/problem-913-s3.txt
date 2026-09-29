#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           isdigit((unsigned char)string[length - 1U]) != 0;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF || character == '\n' || character == '\r') {
            if (character == '\r') {
                int next = fgetc(stream);

                if (next != '\n' && next != EOF) {
                    if (ungetc(next, stream) == EOF) {
                        free(buffer);
                        return NULL;
                    }
                }
            }

            if (character == EOF && ferror(stream) != 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *input;
    size_t length;

    input = read_line(stdin, &length);

    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    free(input);
    return 0;
}