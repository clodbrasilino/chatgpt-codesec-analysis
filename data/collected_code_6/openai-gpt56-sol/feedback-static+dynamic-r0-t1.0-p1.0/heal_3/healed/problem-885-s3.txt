#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch = EOF;

    if (line == NULL) {
        return false;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return false;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;

    return true;
}

static bool are_isomorphic(const char *first, const char *second)
{
    int first_to_second[256];
    int second_to_first[256];
    size_t i;

    if (first == NULL || second == NULL) {
        return false;
    }

    for (i = 0; i < 256; ++i) {
        first_to_second[i] = -1;
        second_to_first[i] = -1;
    }

    for (i = 0; first[i] != '\0' && second[i] != '\0'; ++i) {
        unsigned char first_char = (unsigned char)first[i];
        unsigned char second_char = (unsigned char)second[i];

        if (first_to_second[first_char] == -1 &&
            second_to_first[second_char] == -1) {
            first_to_second[first_char] = (int)second_char;
            second_to_first[second_char] = (int)first_char;
        } else if (first_to_second[first_char] != (int)second_char ||
                   second_to_first[second_char] != (int)first_char) {
            return false;
        }
    }

    return first[i] == '\0' && second[i] == '\0';
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    int result = EXIT_FAILURE;

    if (!read_line(&first) || !read_line(&second)) {
        goto cleanup;
    }

    puts(are_isomorphic(first, second) ? "Isomorphic" : "Not isomorphic");
    result = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return result;
}