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

    char *newline = memchr(buffer, '\n', capacity);

    if (newline != NULL) {
        *newline = '\0';
        return true;
    }

    if (memchr(buffer, '\0', capacity) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    buffer[0] = '\0';
    return false;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    const char *first_end = memchr(first, '\0', MAX_INPUT_LENGTH + 1U);
    const char *second_end = memchr(second, '\0', MAX_INPUT_LENGTH + 1U);

    if (first_end == NULL || second_end == NULL) {
        return false;
    }

    size_t first_length = (size_t)(first_end - first);
    size_t second_length = (size_t)(second_end - second);

    if (first_length != second_length) {
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

    memmove(doubled, first, first_length);
    memmove(doubled + first_length, first, first_length);
    doubled[doubled_length] = '\0';

    bool result = strstr(doubled, second) != NULL;

    free(doubled);
    return result;
}

int main(void)
{
    char first[MAX_INPUT_LENGTH + 1U] = {0};
    char second[MAX_INPUT_LENGTH + 1U] = {0};

    if (!read_line(first, sizeof first) ||
        !read_line(second, sizeof second)) {
        return EXIT_FAILURE;
    }

    if (puts(are_rotations(first, second) ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}