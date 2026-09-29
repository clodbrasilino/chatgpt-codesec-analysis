#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t length = strnlen(buffer, capacity);

    if (length == capacity) {
        buffer[capacity - 1U] = '\0';
        return false;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return false;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    size_t first_length = strnlen(first, MAX_INPUT_LENGTH + 1U);
    size_t second_length = strnlen(second, MAX_INPUT_LENGTH + 1U);

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

    size_t doubled_length = first_length * 2U;
    char *doubled = malloc(doubled_length + 1U);

    if (doubled == NULL) {
        return false;
    }

    for (size_t i = 0U; i < doubled_length; ++i) {
        doubled[i] = first[i % first_length];
    }
    doubled[doubled_length] = '\0';

    bool result = strstr(doubled, second) != NULL;

    free(doubled);
    return result;
}

int main(void)
{
    char *first = calloc(MAX_INPUT_LENGTH + 1U, sizeof *first);
    char *second = calloc(MAX_INPUT_LENGTH + 1U, sizeof *second);

    if (first == NULL || second == NULL) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (!read_line(first, MAX_INPUT_LENGTH + 1U) ||
        !read_line(second, MAX_INPUT_LENGTH + 1U)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");

    free(first);
    free(second);
    return EXIT_SUCCESS;
}