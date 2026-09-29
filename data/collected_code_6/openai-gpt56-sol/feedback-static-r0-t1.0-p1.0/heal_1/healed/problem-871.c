#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    char *combined;
    bool result;

    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    combined = malloc((2U * first_length) + 1U);
    if (combined == NULL) {
        return false;
    }

    memcpy(combined, first, first_length);
    memcpy(combined + first_length, first, first_length);
    combined[2U * first_length] = '\0';

    result = strstr(combined, second) != NULL;
    free(combined);

    return result;
}

static bool read_line(char **line, size_t *length)
{
    size_t capacity = 128U;
    int character;
    char *buffer;

    if (line == NULL || length == NULL) {
        return false;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    *length = 0U;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (*length > SIZE_MAX - 2U) {
            free(buffer);
            return false;
        }

        if (*length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[*length] = (char)character;
        ++*length;
    }

    if (character == EOF && *length == 0U) {
        free(buffer);
        return false;
    }

    if (*length > 0U && buffer[*length - 1U] == '\r') {
        --*length;
    }

    buffer[*length] = '\0';
    *line = buffer;
    return true;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length;
    size_t second_length;
    int status = EXIT_FAILURE;

    if (!read_line(&first, &first_length)) {
        goto cleanup;
    }

    if (!read_line(&second, &second_length)) {
        goto cleanup;
    }

    if (are_rotations(first, first_length, second, second_length)) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    status = EXIT_SUCCESS;

cleanup:
    free(first);
    free(second);
    return status;
}