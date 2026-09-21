#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_only_allowed_characters(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string;
         *p != '\0';
         ++p) {
        if (!((*p >= 'A' && *p <= 'Z') ||
              (*p >= 'a' && *p <= 'z') ||
              (*p >= '0' && *p <= '9'))) {
            return false;
        }
    }

    return true;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
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

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");
    free(input);

    return 0;
}