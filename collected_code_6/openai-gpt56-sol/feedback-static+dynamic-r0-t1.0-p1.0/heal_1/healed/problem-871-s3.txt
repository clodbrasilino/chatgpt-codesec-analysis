#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    char *newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return false;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    const size_t first_length = strnlen(first, INPUT_CAPACITY);
    const size_t second_length = strnlen(second, INPUT_CAPACITY);

    if (first_length == INPUT_CAPACITY ||
        second_length == INPUT_CAPACITY ||
        first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    const size_t buffer_size = first_length * 2U + 1U;
    char *doubled = malloc(buffer_size);
    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[buffer_size - 1U] = '\0';

    const bool result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char first[INPUT_CAPACITY];
    char second[INPUT_CAPACITY];

    if (!read_line(first, sizeof(first)) ||
        !read_line(second, sizeof(second))) {
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}