#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LENGTH 4096U

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_character = (unsigned char)*left;
        unsigned char right_character = (unsigned char)*right;

        if (tolower(left_character) != tolower(right_character)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static bool month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    if (month == NULL) {
        return false;
    }

    for (size_t i = 0U; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool discard_remainder(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return false;
    }

    do {
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stream);
}

static char *read_line(FILE *stream)
{
    char *line;
    size_t capacity = 128U;
    size_t length = 0U;
    int character;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        if (length == MAXIMUM_LENGTH) {
            free(line);

            if (!discard_remainder(stream)) {
                return NULL;
            }

            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity * 2U;

            if (new_capacity > MAXIMUM_LENGTH + 1U) {
                new_capacity = MAXIMUM_LENGTH + 1U;
            }

            char *resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stream) || length == 0U) {
            free(line);
            return NULL;
        }
    }

    if (length > 0U && line[length - 1U] == '\r') {
        --length;
    }

    line[length] = '\0';

    char *resized = realloc(line, length + 1U);
    return resized != NULL ? resized : line;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}