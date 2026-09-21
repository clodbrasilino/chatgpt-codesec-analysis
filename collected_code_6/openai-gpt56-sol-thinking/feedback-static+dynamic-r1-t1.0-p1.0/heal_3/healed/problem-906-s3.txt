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

enum {
    DATE_MATCH_COUNT = 6
};

static int parse_digits(const char *text, const regmatch_t *match)
{
    int value = 0;

    for (regoff_t index = match->rm_so; index < match->rm_eo; ++index) {
        value = value * 10 + (text[index] - '0');
    }

    return value;
}

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int days_in_month(int year, int month)
{
    switch (month) {
        case 2:
            return is_leap_year(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        default:
            return 0;
    }
}

static int is_valid_date(int year, int month, int day)
{
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    return day <= days_in_month(year, month);
}

int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    static const char pattern[] =
        "([0-9]{4})([-/])([0-9]{2})([-/])([0-9]{2})";
    regex_t regex;
    regmatch_t matches[DATE_MATCH_COUNT];
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

        result = regexec(&regex, cursor, DATE_MATCH_COUNT, matches, 0);

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
            const int candidate_year = parse_digits(cursor, &matches[1]);
            const int candidate_month = parse_digits(cursor, &matches[3]);
            const int candidate_day = parse_digits(cursor, &matches[5]);

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

int main(int argc, char **const argv)
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

    switch (result) {
        case DATE_FOUND:
            printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
                   year, month, day);
            return EXIT_SUCCESS;

        case DATE_NOT_FOUND:
            fprintf(stderr, "No valid date found in the URL\n");
            break;

        case DATE_INVALID_ARGUMENT:
            fprintf(stderr, "Invalid argument\n");
            break;

        default:
            fprintf(stderr, "Regular expression processing failed\n");
            break;
    }

    return EXIT_FAILURE;
}