#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_match_number(const char *source, regmatch_t match,
                              long minimum, long maximum, int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[5];
    char *end;
    long number;
    regoff_t match_length;
    size_t length;

    if (source == NULL || value == NULL ||
        match.rm_so < 0 || match.rm_eo < match.rm_so) {
        return -1;
    }

    match_length = match.rm_eo - match.rm_so;
    if ((uintmax_t)match_length >= (uintmax_t)sizeof(buffer)) {
        return -1;
    }

    length = (size_t)match_length;

    for (size_t i = 0; i < length; ++i) {
        char character = source[match.rm_so + (regoff_t)i];

        if (character < '0' || character > '9') {
            return -1;
        }

        buffer[i] = character;
    }

    buffer[length] = '\0';

    errno = 0;
    number = strtol(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        number < minimum || number > maximum ||
        number < INT_MIN || number > INT_MAX) {
        return 1;
    }

    *value = (int)number;
    return 0;
}

static int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static int is_valid_date(int year, int month, int day)
{
    static const int days_per_month[12] = {
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

    result = regexec(&regex, url,
                     sizeof(matches) / sizeof(matches[0]), matches, 0);

    if (result != 0) {
        regfree(&regex);
        return result == REG_NOMATCH ? 1 : -1;
    }

    result = parse_match_number(url, matches[2], 1, 9999, &parsed_year);

    if (result == 0) {
        result = parse_match_number(url, matches[3], 1, 12, &parsed_month);
    }

    if (result == 0) {
        result = parse_match_number(url, matches[4], 1, 31, &parsed_day);
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

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *url;
    int year;
    int month;
    int day;
    int result;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "date-from-url";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    url = argv[1];
    result = extract_date_from_url(url, &year, &month, &day);

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