#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef enum {
    DATE_EXTRACT_OK,
    DATE_EXTRACT_NOT_FOUND,
    DATE_EXTRACT_INVALID_DATE,
    DATE_EXTRACT_REGEX_ERROR,
    DATE_EXTRACT_INVALID_ARGUMENT
} DateExtractStatus;

static bool parse_component(const char *url, regmatch_t match,
                            regoff_t expected_length, int *value)
{
    int result = 0;

    if (url == NULL || value == NULL || match.rm_so < 0 ||
        match.rm_eo < match.rm_so ||
        match.rm_eo - match.rm_so != expected_length) {
        return false;
    }

    for (regoff_t i = match.rm_so; i < match.rm_eo; ++i) {
        if (url[i] < '0' || url[i] > '9') {
            return false;
        }

        result = result * 10 + (url[i] - '0');
    }

    *value = result;
    return true;
}

static bool is_valid_date(int year, int month, int day)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maximum_day;
    bool leap_year;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    maximum_day = days_per_month[month - 1];
    leap_year = (year % 4 == 0 && year % 100 != 0) ||
                year % 400 == 0;

    if (month == 2 && leap_year) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

DateExtractStatus extract_date_from_url(const char *url, int *year,
                                        int *month, int *day)
{
    static const char pattern[] =
        "(^|[^0-9])"
        "(([0-9]{4})/(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])|"
        "([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01]))"
        "([^0-9]|$)";

    regex_t regex;
    regmatch_t matches[10];
    int regex_result;
    size_t year_index;
    size_t month_index;
    size_t day_index;
    int extracted_year;
    int extracted_month;
    int extracted_day;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return DATE_EXTRACT_INVALID_ARGUMENT;
    }

    regex_result = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_result != 0) {
        return DATE_EXTRACT_REGEX_ERROR;
    }

    regex_result = regexec(
        &regex,
        url,
        sizeof matches / sizeof matches[0],
        matches,
        0
    );

    regfree(&regex);

    if (regex_result == REG_NOMATCH) {
        return DATE_EXTRACT_NOT_FOUND;
    }

    if (regex_result != 0) {
        return DATE_EXTRACT_REGEX_ERROR;
    }

    if (matches[3].rm_so >= 0) {
        year_index = 3;
        month_index = 4;
        day_index = 5;
    } else {
        year_index = 6;
        month_index = 7;
        day_index = 8;
    }

    if (!parse_component(url, matches[year_index], 4, &extracted_year) ||
        !parse_component(url, matches[month_index], 2, &extracted_month) ||
        !parse_component(url, matches[day_index], 2, &extracted_day)) {
        return DATE_EXTRACT_REGEX_ERROR;
    }

    if (!is_valid_date(extracted_year, extracted_month, extracted_day)) {
        return DATE_EXTRACT_INVALID_DATE;
    }

    *year = extracted_year;
    *month = extracted_month;
    *day = extracted_day;

    return DATE_EXTRACT_OK;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    int year;
    int month;
    int day;
    DateExtractStatus status;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    status = extract_date_from_url(argv[1], &year, &month, &day);

    switch (status) {
        case DATE_EXTRACT_OK:
            printf("Year: %04d\nMonth: %02d\nDay: %02d\n",
                   year, month, day);
            return EXIT_SUCCESS;

        case DATE_EXTRACT_NOT_FOUND:
            fputs("No date found in the URL.\n", stderr);
            break;

        case DATE_EXTRACT_INVALID_DATE:
            fputs("The URL contains an invalid date.\n", stderr);
            break;

        case DATE_EXTRACT_REGEX_ERROR:
            fputs("A regular expression error occurred.\n", stderr);
            break;

        case DATE_EXTRACT_INVALID_ARGUMENT:
            fputs("Invalid argument.\n", stderr);
            break;

        default:
            fputs("An unexpected error occurred.\n", stderr);
            break;
    }

    return EXIT_FAILURE;
}