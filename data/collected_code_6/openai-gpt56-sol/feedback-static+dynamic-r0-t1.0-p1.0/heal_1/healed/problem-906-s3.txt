#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int match_to_int(const char *source, regmatch_t match, int *value)
{
    char buffer[32];
    size_t length;
    char *end;
    long parsed;

    if (source == NULL || value == NULL ||
        match.rm_so < 0 || match.rm_eo < match.rm_so) {
        return -1;
    }

    length = (size_t)(match.rm_eo - match.rm_so);
    if (length == 0 || length >= sizeof(buffer)) {
        return -1;
    }

    if (snprintf(buffer, sizeof(buffer), "%.*s", (int)length,
                 source + match.rm_so) != (int)length) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtol(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
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

    if (year < 1 || year > 9999 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    maximum_day = days_per_month[month - 1];
    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

static int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    static const char pattern[] =
        "(^|[^0-9])([0-9]{4})[-/]([0-9]{2})[-/]([0-9]{2})([^0-9]|$)";
    regex_t regex;
    regmatch_t matches[6];
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

    result = regexec(&regex, url, sizeof(matches) / sizeof(matches[0]),
                     matches, 0);
    if (result != 0) {
        regfree(&regex);
        return result == REG_NOMATCH ? 1 : -1;
    }

    if (match_to_int(url, matches[2], &parsed_year) != 0 ||
        match_to_int(url, matches[3], &parsed_month) != 0 ||
        match_to_int(url, matches[4], &parsed_day) != 0) {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);

    if (!is_valid_date(parsed_year, parsed_month, parsed_day)) {
        return 1;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return 0;
}

int main(int argc, char *argv[])
{
    int year;
    int month;
    int day;
    int result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <url>\n", program);
        return EXIT_FAILURE;
    }

    result = extract_date_from_url(argv[1], &year, &month, &day);
    if (result == 1) {
        fprintf(stderr, "No valid date found\n");
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fprintf(stderr, "Failed to extract date\n");
        return EXIT_FAILURE;
    }

    if (printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
               year, month, day) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}