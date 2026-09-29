#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int toggle_case(char *str)
{
    unsigned char *p;

    if (str == NULL) {
        return -1;
    }

    p = (unsigned char *)str;

    while (*p != '\0') {
        if (islower(*p)) {
            *p = (unsigned char)toupper(*p);
        } else if (isupper(*p)) {
            *p = (unsigned char)tolower(*p);
        }

        ++p;
    }

    return 0;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        size_t required;

        if (length > SIZE_MAX - 2) {
            fputs("Input is too large\n", stderr);
            free(buffer);
            return EXIT_FAILURE;
        }

        required = length + 2;

        if (capacity < required) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *new_buffer;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }

                new_capacity *= 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                fputs("Memory allocation failed\n", stderr);
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    buffer[length] = '\0';

    if (toggle_case(buffer) != 0) {
        fputs("Invalid string\n", stderr);
        free(buffer);
        return EXIT_FAILURE;
    }

    if (fwrite(buffer, sizeof *buffer, length, stdout) != length) {
        perror("fwrite");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}