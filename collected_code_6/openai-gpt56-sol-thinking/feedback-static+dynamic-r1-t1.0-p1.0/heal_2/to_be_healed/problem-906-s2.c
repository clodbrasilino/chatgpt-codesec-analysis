#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

enum ExtractResult {
    EXTRACT_SUCCESS = 0,
    EXTRACT_NOT_FOUND,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_REGEX_ERROR,
    EXTRACT_INVALID_DATE
};

static int parse_match(const char *text, regmatch_t match, int *value)
{
    regoff_t i;
    regoff_t length;
    int result = 0;

    if (text == NULL || value == NULL ||
        match.rm_so < 0 || match.rm_eo <= match.rm_so) {
        return 0;
    }

    length = match.rm_eo - match.rm_so;
    if (length > 4) {
        return 0;
    }

    for (i = match.rm_so; i < match.rm_eo; ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return 0;
        }

        result = result * 10 + (text[i] - '0');
    }

    *value = result;
    return 1;
}

static int is_leap_year(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
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
        "(^|[^0-9])([0-9]{4})([-/])([0-9]{1,2})\\3([0-9]{1,2})([^0-9]|$)";
    regex_t regex;
    regmatch_t matches[8];
    int regex_result;
    int parsed_year;
    int parsed_month;
    int parsed_day;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    regex_result = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_result != 0) {
        return EXTRACT_REGEX_ERROR;
    }

    regex_result = regexec(&regex, url, 8, matches, 0);
    if (regex_result != 0) {
        regfree(&regex);
        return regex_result == REG_NOMATCH
            ? EXTRACT_NOT_FOUND
            : EXTRACT_REGEX_ERROR;
    }

    if (!parse_match(url, matches[2], &parsed_year) ||
        !parse_match(url, matches[4], &parsed_month) ||
        !parse_match(url, matches[6], &parsed_day)) {
        regfree(&regex);
        return EXTRACT_INVALID_DATE;
    }

    regfree(&regex);

    if (!is_valid_date(parsed_year, parsed_month, parsed_day)) {
        return EXTRACT_INVALID_DATE;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return EXTRACT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
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

    if (result != EXTRACT_SUCCESS) {
        switch (result) {
        case EXTRACT_NOT_FOUND:
            fprintf(stderr, "No date found in the URL\n");
            break;
        case EXTRACT_INVALID_DATE:
            fprintf(stderr, "The URL contains an invalid date\n");
            break;
        case EXTRACT_INVALID_ARGUMENT:
            fprintf(stderr, "Invalid argument\n");
            break;
        default:
            fprintf(stderr, "Unable to extract the date\n");
            break;
        }

        return EXIT_FAILURE;
    }

    if (printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
               year, month, day) < 0 ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}