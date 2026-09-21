#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return 0;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int read_month(char **month)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    if (month == NULL) {
        return -1;
    }

    *month = NULL;
    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    if (length == 0) {
        free(line);
        return 1;
    }

    *month = line;
    return 0;
}

int main(void)
{
    char *month = NULL;
    int result = read_month(&month);

    if (result < 0) {
        fputs("Failed to read the month.\n", stderr);
        return EXIT_FAILURE;
    }

    if (result > 0) {
        fputs("Month name cannot be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");
    free(month);

    return EXIT_SUCCESS;
}