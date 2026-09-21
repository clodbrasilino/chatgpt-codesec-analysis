#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return true;
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

    size_t first_length = strlen(first);
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    size_t buffer_size = first_length * 2U + 1U;
    char *doubled = malloc(buffer_size);

    if (doubled == NULL) {
        return false;
    }

    for (size_t i = 0U; i < first_length; ++i) {
        doubled[i] = first[i];
        doubled[first_length + i] = first[i];
    }

    doubled[2U * first_length] = '\0';

    bool result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char *first = malloc(INPUT_CAPACITY);
    char *second = malloc(INPUT_CAPACITY);

    if (first == NULL || second == NULL) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (!read_line(first, INPUT_CAPACITY) ||
        !read_line(second, INPUT_CAPACITY)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");

    free(first);
    free(second);

    return EXIT_SUCCESS;
}