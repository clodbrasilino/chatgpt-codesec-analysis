#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char **output)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer;
    int ch;

    if (output == NULL) {
        return false;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            free(buffer);
            return false;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (SIZE_MAX / 2U)) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2U;
            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *output = buffer;
    return true;
}

static bool are_rotations(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t allocation_size;
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strnlen(first, MAX_INPUT_LENGTH + 1U);
    second_length = strnlen(second, MAX_INPUT_LENGTH + 1U);

    if (first_length > MAX_INPUT_LENGTH ||
        second_length > MAX_INPUT_LENGTH ||
        first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    allocation_size = (2U * first_length) + 1U;
    combined = malloc(allocation_size);
    if (combined == NULL) {
        return false;
    }

    memcpy(combined, first, first_length);
    memcpy(combined + first_length, first, first_length);
    combined[allocation_size - 1U] = '\0';

    result = strstr(combined, second) != NULL;
    free(combined);

    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    bool result;

    if (!read_line(&first) || !read_line(&second)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    result = are_rotations(first, second);

    free(first);
    free(second);

    if (result) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    return EXIT_SUCCESS;
}