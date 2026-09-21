#include <stdio.h>
#include <stdlib.h>

enum ExtractResult {
    EXTRACT_SUCCESS = 0,
    EXTRACT_NOT_FOUND,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_REGEX_ERROR,
    EXTRACT_INVALID_DATE
};

static int is_digit(char character)
{
    return character >= '0' && character <= '9';
}

static int is_separator(char character)
{
    return character == '-' || character == '/';
}

static int is_leap_year(int year)
{
    return year % 400 == 0 ||
           (year % 4 == 0 && year % 100 != 0);
}

static int is_valid_date(int year, int month, int day)
{
    int maximum_day;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return 0;
    }

    switch (month) {
    case 2:
        maximum_day = is_leap_year(year) ? 29 : 28;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        maximum_day = 30;
        break;

    default:
        maximum_day = 31;
        break;
    }

    return day <= maximum_day;
}

int extract_date_from_url(const char *url, int *year, int *month, int *day)
{
    const char *position;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (position = url; *position != '\0'; ++position) {
        const char *cursor;
        char first_separator;
        char second_separator;
        int parsed_year = 0;
        int parsed_month;
        int parsed_day;
        int digit_count;

        if (position != url && is_digit(position[-1])) {
            continue;
        }

        cursor = position;

        for (digit_count = 0; digit_count < 4; ++digit_count) {
            if (!is_digit(*cursor)) {
                break;
            }

            parsed_year = parsed_year * 10 + (*cursor - '0');
            ++cursor;
        }

        if (digit_count != 4 || !is_separator(*cursor)) {
            continue;
        }

        first_separator = *cursor;
        ++cursor;

        if (!is_digit(*cursor)) {
            continue;
        }

        parsed_month = *cursor - '0';
        ++cursor;

        if (is_digit(*cursor)) {
            parsed_month = parsed_month * 10 + (*cursor - '0');
            ++cursor;
        }

        if (!is_separator(*cursor)) {
            continue;
        }

        second_separator = *cursor;
        ++cursor;

        if (!is_digit(*cursor)) {
            continue;
        }

        parsed_day = *cursor - '0';
        ++cursor;

        if (is_digit(*cursor)) {
            parsed_day = parsed_day * 10 + (*cursor - '0');
            ++cursor;
        }

        if (is_digit(*cursor)) {
            continue;
        }

        if (first_separator != second_separator ||
            !is_valid_date(parsed_year, parsed_month, parsed_day)) {
            return EXTRACT_INVALID_DATE;
        }

        *year = parsed_year;
        *month = parsed_month;
        *day = parsed_day;

        return EXTRACT_SUCCESS;
    }

    return EXTRACT_NOT_FOUND;
}

int main(int argc, char *argv[const])
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

        case EXTRACT_REGEX_ERROR:
        default:
            fprintf(stderr, "Unable to extract the date\n");
            break;
        }

        return EXIT_FAILURE;
    }

    if (printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
               year, month, day) < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}