#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        buffer[0] = '\0';
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

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t index = 0U;

        while (index < first_length &&
               first[index] == second[(index + offset) % first_length]) {
            ++index;
        }

        if (index == first_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char first[INPUT_CAPACITY];
    char second[INPUT_CAPACITY];

    if (!read_line(first, sizeof first) ||
        !read_line(second, sizeof second)) {
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");
    return EXIT_SUCCESS;
}