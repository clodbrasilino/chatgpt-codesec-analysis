#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;

    *line = malloc(capacity);
    if (*line == NULL) {
        return false;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length > 0 && (*line)[length - 1] == '\r') {
            (*line)[--length] = '\0';
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (size_t)-1 / 2) {
                free(*line);
                *line = NULL;
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                free(*line);
                *line = NULL;
                return false;
            }

            *line = resized;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return false;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
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
            first_to_second[first_char] = second_char;
            second_to_first[second_char] = first_char;
        } else if (first_to_second[first_char] != second_char ||
                   second_to_first[second_char] != first_char) {
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

    if (!read_line(&first)) {
        goto cleanup;
    }

    if (!read_line(&second)) {
        goto cleanup;
    }

    puts(are_isomorphic(first, second) ? "Isomorphic" : "Not isomorphic");
    result = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return result;
}