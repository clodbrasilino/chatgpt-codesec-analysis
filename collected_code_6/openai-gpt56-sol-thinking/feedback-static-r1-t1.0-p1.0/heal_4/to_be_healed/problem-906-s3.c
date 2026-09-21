#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    DATE_NOT_FOUND = 0,
    DATE_FOUND = 1,
    DATE_INVALID_ARGUMENT = -1
};

static int is_decimal_digit(char character)
{
    return character >= '0' && character <= '9';
}

static int parse_two_digits(const char *text)
{
    return (text[0] - '0') * 10 +
           (text[1] - '0');
}

static int parse_four_digits(const char *text)
{
    return (text[0] - '0') * 1000 +
           (text[1] - '0') * 100 +
           (text[2] - '0') * 10 +
           (text[3] - '0');
}

static int is_leap_year(int year)
{
    return year % 4 == 0 &&
           (year % 100 != 0 || year % 400 == 0);
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
    size_t length;
    size_t index;

    if (url == NULL || year == NULL || month == NULL || day == NULL) {
        return DATE_INVALID_ARGUMENT;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(url);

    if (length < 10) {
        return DATE_NOT_FOUND;
    }

    for (index = 0; index <= length - 10; ++index) {
        const char *candidate = url + index;
        char separator;
        int candidate_year;
        int candidate_month;
        int candidate_day;

        if (index > 0 && is_decimal_digit(url[index - 1])) {
            continue;
        }

        if (index + 10 < length && is_decimal_digit(url[index + 10])) {
            continue;
        }

        if (!is_decimal_digit(candidate[0]) ||
            !is_decimal_digit(candidate[1]) ||
            !is_decimal_digit(candidate[2]) ||
            !is_decimal_digit(candidate[3]) ||
            !is_decimal_digit(candidate[5]) ||
            !is_decimal_digit(candidate[6]) ||
            !is_decimal_digit(candidate[8]) ||
            !is_decimal_digit(candidate[9])) {
            continue;
        }

        separator = candidate[4];

        if ((separator != '-' && separator != '/') ||
            candidate[7] != separator) {
            continue;
        }

        candidate_year = parse_four_digits(candidate);
        candidate_month = parse_two_digits(candidate + 5);
        candidate_day = parse_two_digits(candidate + 8);

        if (!is_valid_date(candidate_year,
                           candidate_month,
                           candidate_day)) {
            continue;
        }

        *year = candidate_year;
        *month = candidate_month;
        *day = candidate_day;
        return DATE_FOUND;
    }

    return DATE_NOT_FOUND;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    int year;
    int month;
    int day;
    int result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <url>\n", program_name);
        return EXIT_FAILURE;
    }

    result = extract_date_from_url(argv[1], &year, &month, &day);

    if (result == DATE_FOUND) {
        printf("Year: %04d\nMonth: %02d\nDate: %02d\n",
               year, month, day);
        return EXIT_SUCCESS;
    }

    if (result == DATE_NOT_FOUND) {
        fprintf(stderr, "No valid date found in the URL\n");
    } else {
        fprintf(stderr, "Invalid argument\n");
    }

    return EXIT_FAILURE;
}