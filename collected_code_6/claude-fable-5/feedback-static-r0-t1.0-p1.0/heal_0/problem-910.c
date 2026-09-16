#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_leap_year(int year);
static int days_in_month(int month, int year);
static bool is_valid_date(int day, int month, int year);

static bool is_leap_year(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}

static int days_in_month(int month, int year)
{
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12) {
        return 0;
    }

    if (month == 2 && is_leap_year(year)) {
        return 29;
    }

    return days[month - 1];
}

static bool is_valid_date(int day, int month, int year)
{
    if (year < 1583 || year > 9999) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > days_in_month(month, year)) {
        return false;
    }

    return true;
}

int main(void)
{
    int day;
    int month;
    int year;
    int result;

    printf("Enter date (day month year): ");

    result = scanf("%d %d %d", &day, &month, &year);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input format\n");
        return EXIT_FAILURE;
    }

    if (is_valid_date(day, month, year)) {
        printf("%04d-%02d-%02d is a valid Gregorian date\n", year, month, day);
    } else {
        printf("%d-%d-%d is not a valid Gregorian date\n", year, month, day);
    }

    return EXIT_SUCCESS;
}