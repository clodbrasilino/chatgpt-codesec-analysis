#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DATE_EXTRACT_OK,
    DATE_EXTRACT_NOT_FOUND,
    DATE_EXTRACT_INVALID_DATE,
    DATE_EXTRACT_REGEX_ERROR,
    DATE_EXTRACT_INVALID_ARGUMENT
} DateExtractStatus;

static bool is_ascii_digit(char character)
{
    return character >= '0' && character <= '9';
}

static bool parse_component(const char *text, size_t text_length,
                            size_t offset, size_t component_length,
                            int *value)
{
    int result = 0;

    if (text == NULL || value == NULL || offset > text_length ||
        component_length > text_length - offset) {
        return false;
    }

    for (size_t i = 0; i < component_length; ++i) {
        int digit;

        if (!is_ascii_digit(text[offset + i])) {
            return false;
        }

        digit = text[offset + i] - '0';

        if (result > (INT_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
    }

    *value = result;
    return true;
}

static bool is_valid_date(int year, int month, int day)
{
    int maximum_day;
    bool leap_year;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    switch (month) {
        case 2:
            maximum_day = 28;
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
    const size_t date_length = 10;
    size_t url_length;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return DATE_EXTRACT_INVALID_ARGUMENT;
    }

    url_length = strlen(url);

    if (url_length < date_length) {
        return DATE_EXTRACT_NOT_FOUND;
    }

    for (size_t offset = 0; offset <= url_length - date_length; ++offset) {
        char separator;
        int extracted_year;
        int extracted_month;
        int extracted_day;

        if (offset > 0 && is_ascii_digit(url[offset - 1])) {
            continue;
        }

        if (offset + date_length < url_length &&
            is_ascii_digit(url[offset + date_length])) {
            continue;
        }

        separator = url[offset + 4];

        if ((separator != '/' && separator != '-') ||
            url[offset + 7] != separator) {
            continue;
        }

        if (!parse_component(url, url_length, offset, 4,
                             &extracted_year) ||
            !parse_component(url, url_length, offset + 5, 2,
                             &extracted_month) ||
            !parse_component(url, url_length, offset + 8, 2,
                             &extracted_day)) {
            continue;
        }

        if (extracted_month < 1 || extracted_month > 12 ||
            extracted_day < 1 || extracted_day > 31) {
            continue;
        }

        if (!is_valid_date(extracted_year, extracted_month,
                           extracted_day)) {
            return DATE_EXTRACT_INVALID_DATE;
        }

        *year = extracted_year;
        *month = extracted_month;
        *day = extracted_day;

        return DATE_EXTRACT_OK;
    }

    return DATE_EXTRACT_NOT_FOUND;
}

int main(int argc, char **argv)
{
    int year;
    int month;
    int day;
    DateExtractStatus status;
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
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