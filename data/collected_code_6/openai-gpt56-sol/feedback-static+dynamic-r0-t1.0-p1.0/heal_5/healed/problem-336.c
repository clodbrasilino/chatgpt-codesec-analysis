#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    const size_t month_count = sizeof(months) / sizeof(months[0]);

    if (month == NULL) {
        return false;
    }

    for (size_t i = 0U; i < month_count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(char *buffer, size_t capacity, FILE *stream)
{
    size_t length = 0U;
    bool complete = false;
    int ch;

    if (buffer == NULL || capacity < 2U || stream == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            complete = true;
            break;
        }

        if (length + 1U < capacity) {
            buffer[length++] = (char)ch;
        } else {
            do {
                ch = fgetc(stream);
            } while (ch != '\n' && ch != EOF);

            buffer[0] = '\0';
            return false;
        }
    }

    if (ferror(stream)) {
        buffer[0] = '\0';
        return false;
    }

    if (ch == EOF && length == 0U) {
        buffer[0] = '\0';
        return false;
    }

    if (ch == EOF) {
        complete = true;
    }

    if (!complete) {
        buffer[0] = '\0';
        return false;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return true;
}

int main(void)
{
    char month[INPUT_SIZE] = {0};

    if (!read_line(month, sizeof(month), stdin)) {
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