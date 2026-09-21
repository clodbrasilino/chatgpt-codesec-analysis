#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_match(const char *source, const regmatch_t *match,
                       long minimum, long maximum, int *output)
{
    const char *cursor;
    size_t length;
    long value = 0;

    if (source == NULL || match == NULL || output == NULL ||
        match->rm_so < 0 || match->rm_eo < match->rm_so) {
        return -1;
    }

    length = (size_t)(match->rm_eo - match->rm_so);
    if (length == 0) {
        return 1;
    }

    cursor = source + match->rm_so;

    for (size_t i = 0; i < length; ++i) {
        unsigned int digit;

        if (cursor[i] < '0' || cursor[i] > '9') {
            return 1;
        }

        digit = (unsigned int)(cursor[i] - '0');

        if (value > (LONG_MAX - (long)digit) / 10) {
            return 1;
        }

        value = value * 10 + (long)digit;
    }

    if (value < minimum || value > maximum || value > INT_MAX) {
        return 1;
    }

    *output = (int)value;
    return 0;
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

    if (year < 1 || year > 9999 ||
        month < 1 || month > 12 ||
        day < 1) {
        return 0;
    }

    maximum_day = days_per_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

static int extract_date_from_url(const char *url, int *year,
                                 int *month, int *day)
{
    static const char pattern[] =
        "([^0-9]|^)([0-9]{4})([-/])([0-9]{2})\\3([0-9]{2})([^0-9]|$)";
    regex_t regex;
    regmatch_t matches[7];
    int parsed_year;
    int parsed_month;
    int parsed_day;
    int result;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, url,
                     sizeof(matches) / sizeof(matches[0]),
                     matches, 0);

    if (result != 0) {
        regfree(&regex);
        return result == REG_NOMATCH ? 1 : -1;
    }

    result = parse_match(url, &matches[2], 1, 9999, &parsed_year);

    if (result == 0) {
        result = parse_match(url, &matches[4], 1, 12, &parsed_month);
    }

    if (result == 0) {
        result = parse_match(url, &matches[5], 1, 31, &parsed_day);
    }

    regfree(&regex);

    if (result != 0) {
        return result;
    }

    if (!is_valid_date(parsed_year, parsed_month, parsed_day)) {
        return 1;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return 0;
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
        fprintf(stderr, "Usage: %s <url>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "date_extractor");
        return EXIT_FAILURE;
    }

    result = extract_date_from_url(argv[1], &year, &month, &day);

    if (result != 0) {
        fputs("Unable to extract a valid date from the URL\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
           year, month, day);

    return EXIT_SUCCESS;
}