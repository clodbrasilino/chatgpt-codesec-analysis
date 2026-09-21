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

    size_t length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

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

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[doubled_length] = '\0';

    bool result = strstr(doubled, second) != NULL;

    free(doubled);
    return result;
}

int main(void)
{
    char first[MAX_INPUT_LENGTH + 1U];
    char second[MAX_INPUT_LENGTH + 1U];

    if (!read_line(first, sizeof first) ||
        !read_line(second, sizeof second)) {
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}