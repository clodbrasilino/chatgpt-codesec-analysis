#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

enum ExtractResult {
    EXTRACT_SUCCESS = 0,
    EXTRACT_NOT_FOUND,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_REGEX_ERROR,
    EXTRACT_INVALID_DATE,
    EXTRACT_MEMORY_ERROR
};

enum {
    MATCH_COUNT = 6,
    YEAR_MATCH = 2,
    MONTH_MATCH = 3,
    DAY_MATCH = 4
};

static int parse_match(const char *text, regmatch_t match, int *value)
{
    regoff_t position;
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

    for (position = match.rm_so; position < match.rm_eo; ++position) {
        unsigned char character = (unsigned char)text[position];

        if (character < (unsigned char)'0' ||
            character > (unsigned char)'9') {
            return 0;
        }

        result = result * 10 + (int)(character - (unsigned char)'0');
    }

    *value = result;
    return 1;
}

static int is_leap_year(int year)
{
    return year % 400 == 0 ||
           (year % 4 == 0 && year % 100 != 0);
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
    int maximum_day;

    if (year < 1 || day < 1) {
        return 0;
    }

    maximum_day = days_in_month(year, month);
    return maximum_day != 0 && day <= maximum_day;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    static const char pattern[] =
        "(^|[^0-9])([0-9]{4})[-/]([0-9]{1,2})[-/]([0-9]{1,2})([^0-9]|$)";
    regex_t regex;
    regmatch_t *matches;
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

    matches = calloc((size_t)MATCH_COUNT, sizeof(*matches));
    if (matches == NULL) {
        regfree(&regex);
        return EXTRACT_MEMORY_ERROR;
    }

    regex_result = regexec(
        &regex,
        url,
        (size_t)MATCH_COUNT,
        matches,
        0
    );

    if (regex_result != 0) {
        free(matches);
        regfree(&regex);

        if (regex_result == REG_NOMATCH) {
            return EXTRACT_NOT_FOUND;
        }

        return EXTRACT_REGEX_ERROR;
    }

    if (!parse_match(url, matches[YEAR_MATCH], &parsed_year) ||
        !parse_match(url, matches[MONTH_MATCH], &parsed_month) ||
        !parse_match(url, matches[DAY_MATCH], &parsed_day)) {
        free(matches);
        regfree(&regex);
        return EXTRACT_INVALID_DATE;
    }

    free(matches);
    regfree(&regex);

    if (!is_valid_date(parsed_year, parsed_month, parsed_day)) {
        return EXTRACT_INVALID_DATE;
    }

    *year = parsed_year;
    *month = parsed_month;
    *day = parsed_day;

    return EXTRACT_SUCCESS;
}

int main(int argc, char ** const argv)
{
    int year;
    int month;
    int day;
    int result;
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "extract-date";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    result = extract_date_from_url(argv[1], &year, &month, &day);

    switch (result) {
        case EXTRACT_SUCCESS:
            break;

        case EXTRACT_NOT_FOUND:
            fprintf(stderr, "No date found in the URL\n");
            return EXIT_FAILURE;

        case EXTRACT_INVALID_DATE:
            fprintf(stderr, "The URL contains an invalid date\n");
            return EXIT_FAILURE;

        case EXTRACT_MEMORY_ERROR:
            fprintf(stderr, "Insufficient memory\n");
            return EXIT_FAILURE;

        case EXTRACT_INVALID_ARGUMENT:
        case EXTRACT_REGEX_ERROR:
        default:
            fprintf(stderr, "Unable to extract the date\n");
            return EXIT_FAILURE;
    }

    if (printf(
            "Year: %04d\nMonth: %02d\nDate: %02d\n",
            year,
            month,
            day
        ) < 0 ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}