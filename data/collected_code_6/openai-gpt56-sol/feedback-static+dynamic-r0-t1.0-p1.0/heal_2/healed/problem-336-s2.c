#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_MONTH_LENGTH = 31 };

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

static bool month_has_28_days(const char *month)
{
    return equals_ignore_case(month, "February");
}

static bool read_month(char **month)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    if (month == NULL) {
        return false;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (character == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length >= MAX_MONTH_LENGTH) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0)) {
        free(buffer);
        return false;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return false;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    *month = buffer;
    return true;
}

int main(void)
{
    char *month = NULL;

    if (!read_month(&month)) {
        fputs("Failed to read a valid month name.\n", stderr);
        return 1;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return 1;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");

    free(month);
    return 0;
}