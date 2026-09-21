#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return false;
    }

    *line = NULL;
    *capacity = 0;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *temporary;
        size_t new_capacity;

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length == *capacity) {
            if (*capacity == 0) {
                new_capacity = 128;
            } else {
                if (*capacity > SIZE_MAX / 2) {
                    free(*line);
                    *line = NULL;
                    *capacity = 0;
                    return false;
                }
                new_capacity = *capacity * 2;
            }

            temporary = realloc(*line, new_capacity);
            if (temporary == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return false;
            }

            *line = temporary;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return false;
    }

    if (length == SIZE_MAX) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return false;
    }

    if (length + 1 > *capacity) {
        char *temporary = realloc(*line, length + 1);

        if (temporary == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return false;
        }

        *line = temporary;
        *capacity = length + 1;
    }

    (*line)[length] = '\0';
    return true;
}

static bool are_rotations(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    char *doubled;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1) / 2) {
        return false;
    }

    doubled = malloc((first_length * 2) + 1);
    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[first_length * 2] = '\0';

    result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char *first;
    char *second;
    size_t first_capacity;
    size_t second_capacity;
    bool result;

    if (!read_line(&first, &first_capacity)) {
        return EXIT_FAILURE;
    }

    if (!read_line(&second, &second_capacity)) {
        free(first);
        return EXIT_FAILURE;
    }

    result = are_rotations(first, second);

    free(first);
    free(second);

    puts(result ? "Yes" : "No");
    return EXIT_SUCCESS;
}