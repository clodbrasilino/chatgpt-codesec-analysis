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

    for (size_t i = 0U; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(char *buffer, size_t capacity, FILE *stream)
{
    if (buffer == NULL || capacity < 2U || stream == NULL) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return false;
    }

    size_t length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';
        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[length - 1U] = '\0';
        }
        return true;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[length - 1U] = '\0';
        return true;
    }

    if (feof(stream)) {
        return true;
    }

    int ch;
    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return false;
}

int main(void)
{
    char month[INPUT_SIZE];

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