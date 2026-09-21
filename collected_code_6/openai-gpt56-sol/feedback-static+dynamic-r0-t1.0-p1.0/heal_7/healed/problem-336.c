#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 32U

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static bool month_contains_28_days(const char *month)
{
    static const char *const months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
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

static bool discard_line(FILE *stream)
{
    char discard_buffer[128];

    if (stream == NULL) {
        return false;
    }

    for (;;) {
        if (fgets(discard_buffer, sizeof discard_buffer, stream) == NULL) {
            return feof(stream) && !ferror(stream);
        }

        if (memchr(discard_buffer, '\n', sizeof discard_buffer) != NULL) {
            return true;
        }
    }
}

static bool read_line(char *buffer, size_t capacity, FILE *stream)
{
    size_t length;

    if (buffer == NULL || stream == NULL || capacity < 2U || capacity > INT_MAX) {
        return false;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return false;
    }

    length = strnlen(buffer, capacity);

    if (length == capacity) {
        buffer[0] = '\0';
        return false;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[length - 1U] = '\0';
        }

        return true;
    }

    if (feof(stream)) {
        return true;
    }

    buffer[0] = '\0';
    return discard_line(stream) ? false : false;
}

int main(void)
{
    char month[INPUT_SIZE];

    if (!read_line(month, sizeof month, stdin)) {
        fprintf(stderr, "Failed to read a valid month name.\n");
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        return EXIT_FAILURE;
    }

    if (!month_contains_28_days(month)) {
        fprintf(stderr, "Invalid month name.\n");
        return EXIT_FAILURE;
    }

    printf("%s contains 28 days.\n", month);
    return EXIT_SUCCESS;
}