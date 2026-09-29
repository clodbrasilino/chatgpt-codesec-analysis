#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (line == NULL) {
        return -2;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -2;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(buffer);
                    return -2;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(buffer);
                return -2;
            }

            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -3;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -3;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 0;
}

int main(void)
{
    char *input = NULL;
    int result = read_line(&input);

    if (result != 0) {
        if (result == -1) {
            fputs("Memory allocation failure\n", stderr);
        } else if (result == -2) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(frequencies_are_valid(input) ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}