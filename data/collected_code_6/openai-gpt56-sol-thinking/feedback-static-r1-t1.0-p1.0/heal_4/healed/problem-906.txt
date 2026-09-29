#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    DATE_EXTRACT_OK,
    DATE_EXTRACT_NOT_FOUND,
    DATE_EXTRACT_INVALID_DATE,
    DATE_EXTRACT_REGEX_ERROR,
    DATE_EXTRACT_INVALID_ARGUMENT
} DateExtractStatus;

static bool is_decimal_digit(char character)
{
    const unsigned char value = (unsigned char)character;

    return value >= (unsigned char)'0' &&
           value <= (unsigned char)'9';
}

static bool parse_digits(const char *text, size_t length, int *value)
{
    int result = 0;

    if (text == NULL || value == NULL || length == 0) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        int digit;

        if (!is_decimal_digit(text[i])) {
            return false;
        }

        digit = (int)((unsigned char)text[i] - (unsigned char)'0');

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

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    switch (month) {
        case 2:
            maximum_day =
                ((year % 4 == 0 && year % 100 != 0) ||
                 year % 400 == 0) ? 29 : 28;
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

DateExtractStatus extract_date_from_url(const char *url,
                                        size_t url_length,
                                        int *year,
                                        int *month,
                                        int *day)
{
    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return DATE_EXTRACT_INVALID_ARGUMENT;
    }

    for (size_t offset = 0; offset < url_length; ++offset) {
        size_t remaining;
        char separator;
        int extracted_year;
        int extracted_month;
        int extracted_day;

        if (offset > 0 && is_decimal_digit(url[offset - 1])) {
            continue;
        }

        remaining = url_length - offset;

        if (remaining < 10) {
            break;
        }

        separator = url[offset + 4];

        if ((separator != '/' && separator != '-') ||
            url[offset + 7] != separator) {
            continue;
        }

        if (remaining > 10 && is_decimal_digit(url[offset + 10])) {
            continue;
        }

        if (!parse_digits(url + offset, 4, &extracted_year) ||
            !parse_digits(url + offset + 5, 2, &extracted_month) ||
            !parse_digits(url + offset + 8, 2, &extracted_day)) {
            continue;
        }

        if (extracted_month < 1 || extracted_month > 12 ||
            extracted_day < 1 || extracted_day > 31) {
            continue;
        }

        if (!is_valid_date(extracted_year,
                           extracted_month,
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

int main(int argc, char *argv[])
{
    int year;
    int month;
    int day;
    size_t url_length = 0;
    const char *program_name;
    const char *url;
    DateExtractStatus status;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "date_extract";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    url = argv[1];

    while (url[url_length] != '\0') {
        ++url_length;
    }

    status = extract_date_from_url(url, url_length, &year, &month, &day);

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
            fputs("A parsing error occurred.\n", stderr);
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