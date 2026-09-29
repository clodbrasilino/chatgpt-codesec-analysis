#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    for (size_t i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return true;
        }
    }

    return false;
}

static bool read_line(FILE *stream, char *buffer, size_t capacity)
{
    if (stream == NULL || buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return false;
    }

    size_t length = 0;

    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\n' || buffer[length] == '\r') {
        buffer[length] = '\0';
        return true;
    }

    if (buffer[length] == '\0' && !feof(stream)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stream);
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32];

    if (!read_line(stdin, month, sizeof month)) {
        fprintf(stderr, "Failed to read a valid month name.\n");
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    return EXIT_SUCCESS;
}