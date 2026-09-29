#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_number = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        const unsigned char ch = (unsigned char)*str++;

        has_letter = has_letter || isalpha(ch) != 0;
        has_number = has_number || isdigit(ch) != 0;

        if (has_letter && has_number) {
            return true;
        }
    }

    return false;
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
        int ch;

        if (length + 1 >= capacity) {
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

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (has_letter_and_number(input)) {
        puts("The string contains at least one letter and one number.");
    } else {
        puts("The string does not contain at least one letter and one number.");
    }

    free(input);
    return EXIT_SUCCESS;
}