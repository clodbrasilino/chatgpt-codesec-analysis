#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const char *str)
{
    bool seen[256] = { false };

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char character = (unsigned char)*str;

        if (seen[character]) {
            return false;
        }

        seen[character] = true;
        ++str;
    }

    return true;
}

static int read_line(FILE *stream, char **result)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *result = buffer;

    return 0;
}

int main(void)
{
    char *input = NULL;
    int status;

    status = read_line(stdin, &input);
    if (status != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(all_characters_unique(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}