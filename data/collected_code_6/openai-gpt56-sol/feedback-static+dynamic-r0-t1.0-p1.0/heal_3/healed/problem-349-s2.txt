#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_binary_string(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string; *p != '\0'; ++p) {
        if (*p != (unsigned char)'0' && *p != (unsigned char)'1') {
            return false;
        }
    }

    return true;
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

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
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

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else if (feof(stdin)) {
            fputs("No input provided.\n", stderr);
        } else {
            fputs("Unable to allocate memory.\n", stderr);
        }
        return 1;
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");

    free(input);
    return 0;
}