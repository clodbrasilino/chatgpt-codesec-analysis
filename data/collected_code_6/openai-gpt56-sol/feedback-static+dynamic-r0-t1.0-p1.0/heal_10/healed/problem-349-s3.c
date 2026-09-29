#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        ++str;
    }

    return true;
}

static char *read_line(FILE *stream)
{
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    char buffer[256];

    if (stream == NULL) {
        return NULL;
    }

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        size_t chunk_length = strlen(buffer);
        size_t required;
        char *resized;

        if (chunk_length > SIZE_MAX - length - 1) {
            free(line);
            return NULL;
        }

        required = length + chunk_length + 1;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? sizeof buffer : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        memcpy(line + length, buffer, chunk_length);
        length += chunk_length;
        line[length] = '\0';

        if (length > 0 && line[length - 1] == '\n') {
            --length;
            if (length > 0 && line[length - 1] == '\r') {
                --length;
            }
            line[length] = '\0';
            return line;
        }
    }

    if (ferror(stream) || line == NULL) {
        free(line);
        return NULL;
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    return line;
}

int main(void)
{
    char *input = read_line(stdin);
    int result = EXIT_SUCCESS;

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (is_binary_string(input)) {
        if (fputs("Binary string\n", stdout) == EOF) {
            result = EXIT_FAILURE;
        }
    } else {
        if (fputs("Not a binary string\n", stdout) == EOF) {
            result = EXIT_FAILURE;
        }
    }

    free(input);

    if (fflush(stdout) == EOF || ferror(stdout)) {
        result = EXIT_FAILURE;
    }

    return result;
}