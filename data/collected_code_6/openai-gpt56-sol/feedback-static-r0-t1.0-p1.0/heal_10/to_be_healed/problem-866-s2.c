#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

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

static bool month_has_31_days(const char *month)
{
    static const char *const months[] = {
        "January",
        "March",
        "May",
        "July",
        "August",
        "October",
        "December"
    };

    const size_t count = sizeof months / sizeof months[0];

    for (size_t i = 0; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char *buffer, size_t size)
{
    if (stream == NULL || buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)size, stream) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t length = 0;
    while (length < size && buffer[length] != '\0') {
        ++length;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';

        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[--length] = '\0';
        }

        return true;
    }

    if (feof(stream)) {
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return true;
    }

    int character;
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[INPUT_SIZE] = {0};

    if (!read_line(stdin, month, sizeof month)) {
        fputs("Failed to read the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");

    return EXIT_SUCCESS;
}