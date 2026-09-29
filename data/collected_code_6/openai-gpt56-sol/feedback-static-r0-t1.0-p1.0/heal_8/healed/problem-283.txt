#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)text;
         *p != '\0';
         ++p) {
        unsigned int digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return 0;
        }

        digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (length >= capacity - 1) {
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

        ch = fgetc(stream);

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

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);
    int valid;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    valid = has_valid_digit_frequencies(input);
    free(input);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}