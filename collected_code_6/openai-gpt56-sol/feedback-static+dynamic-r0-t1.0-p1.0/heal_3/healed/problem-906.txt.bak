#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_match(const char *source, regmatch_t match,
                       long minimum, long maximum, int *result)
{
    char buffer[5];
    char *end;
    size_t length;
    long value;

    if (source == NULL || result == NULL ||
        match.rm_so < 0 || match.rm_eo < match.rm_so) {
        return -1;
    }

    length = (size_t)(match.rm_eo - match.rm_so);
    if (length == 0 || length >= sizeof buffer) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char c = source[match.rm_so + (regoff_t)i];

        if (c < '0' || c > '9') {
            return -1;
        }

        buffer[i] = c;
    }

    buffer[length] = '\0';

    errno = 0;
    value = strtol(buffer, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        value < minimum || value > maximum) {
        return 1;
    }

    *result = (int)value;
    return 0;
}

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int is_valid_date(int year, int month, int day)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int maximum_day;

    if (year < 1 || year > 9999 || month < 1 || month > 12) {
        return 0;
    }

    maximum_day = days_per_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day >= 1 && day <= maximum_day;
}

static int extract_date_from_url(const char *url,
                                 int *year, int *month, int *day)
{
    static const char pattern[] =
        "([^0-9]|^)([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})([^0-9]|$)";
    regex_t regex;
    regmatch_t matches[6];
    int parsed_year;
    int parsed_month;
    int parsed_day;
    int status;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, url, 6, matches, 0);
    if (status != 0) {
        regfree(&regex);
        return status == REG_NOMATCH ? 1 : -1;
    }

    status = parse_match(url, matches[2], 1, 9999, &parsed_year);

    if (status == 0) {
        status = parse_match(url, matches[3], 1, 12, &parsed_month);
    }

    if (status == 0) {
        status = parse_match(url, matches[4], 1, 31, &parsed_day);
    }

    regfree(&regex);

    if (status != 0) {
        return status;
    }

    if (!is_valid_date(parsed_year, parsed_month, parsed_day)) {
        return 1;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return 0;
}

int main(int argc, char * const argv[])
{
    int year;
    int month;
    int day;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (extract_date_from_url(argv[1], &year, &month, &day) != 0) {
        fprintf(stderr, "Unable to extract a valid date from the URL\n");
        return EXIT_FAILURE;
    }

    printf("Year: %04d\nMonth: %02d\nDate: %02d\n", year, month, day);
    return EXIT_SUCCESS;
}