#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_date(int month, int day)
{
    static const int days_in_month[] = {
        31, 29, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    return month >= 1 && month <= 12 &&
           day >= 1 && day <= days_in_month[month - 1];
}

static const char *get_season(int month, int day)
{
    int date = month * 100 + day;

    if (date >= 1221 || date < 320) {
        return "Winter";
    }

    if (date < 621) {
        return "Spring";
    }

    if (date < 923) {
        return "Summer";
    }

    return "Autumn";
}

static int parse_integer(const char **input, int *value)
{
    char *end;
    long result;

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return 0;
    }

    errno = 0;
    result = strtol(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        result < INT_MIN || result > INT_MAX) {
        return 0;
    }

    *value = (int)result;
    *input = end;
    return 1;
}

int main(void)
{
    char input[128];
    const char *cursor;
    int month;
    int day;

    fputs("Enter month and day: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_integer(&cursor, &month) ||
        !parse_integer(&cursor, &day)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_valid_date(month, day)) {
        fputs("Invalid date.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(get_season(month, day));
    return EXIT_SUCCESS;
}