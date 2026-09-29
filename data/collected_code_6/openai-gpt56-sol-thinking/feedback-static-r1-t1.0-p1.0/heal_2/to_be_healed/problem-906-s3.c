#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    DATE_NOT_FOUND = 0,
    DATE_FOUND = 1,
    DATE_INVALID_ARGUMENT = -1,
    DATE_REGEX_ERROR = -2
};

static int parse_digits(const char *text, regmatch_t match)
{
    int value = 0;
    regoff_t i;

    for (i = match.rm_so; i < match.rm_eo; ++i) {
        value = value * 10 + (text[i] - '0');
    }

    return value;
}

static int is_leap_year(int year)
{
    return year % 4 == 0 &&
           (year % 100 != 0 || year % 400 == 0);
}

static int is_valid_date(int year, int month, int day)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int maximum_day;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    maximum_day = days_per_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    static const char pattern[] =
        "([0-9]{4})([-/])([0-9]{2})([-/])([0-9]{2})";
    regex_t regex;
    regmatch_t matches[6];
    const char *cursor;
    int result;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return DATE_INVALID_ARGUMENT;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return DATE_REGEX_ERROR;
    }

    cursor = url;

    for (;;) {
        const char *start;
        const char *end;

        result = regexec(&regex, cursor, 6, matches, 0);

        if (result == REG_NOMATCH) {
            regfree(&regex);
            return DATE_NOT_FOUND;
        }

        if (result != 0) {
            regfree(&regex);
            return DATE_REGEX_ERROR;
        }

        start = cursor + matches[0].rm_so;
        end = cursor + matches[0].rm_eo;

        if ((start == url || !isdigit((unsigned char)start[-1])) &&
            !isdigit((unsigned char)*end) &&
            cursor[matches[2].rm_so] == cursor[matches[4].rm_so]) {
            int candidate_year = parse_digits(cursor, matches[1]);
            int candidate_month = parse_digits(cursor, matches[3]);
            int candidate_day = parse_digits(cursor, matches[5]);

            if (is_valid_date(candidate_year, candidate_month, candidate_day)) {
                *year = candidate_year;
                *month = candidate_month;
                *day = candidate_day;
                regfree(&regex);
                return DATE_FOUND;
            }
        }

        cursor = start + 1;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int year;
    int month;
    int day;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = extract_date_from_url(argv[1], &year, &month, &day);

    if (result == DATE_FOUND) {
        printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
               year, month, day);
        return EXIT_SUCCESS;
    }

    if (result == DATE_NOT_FOUND) {
        fprintf(stderr, "No valid date found in the URL\n");
    } else if (result == DATE_INVALID_ARGUMENT) {
        fprintf(stderr, "Invalid argument\n");
    } else {
        fprintf(stderr, "Regular expression processing failed\n");
    }

    return EXIT_FAILURE;
}