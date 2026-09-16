#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

static bool is_valid_gregorian_date(int year, int month, int day)
{
    static const int days_per_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int maximum_day;

    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    maximum_day = days_per_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

int main(void)
{
    int year;
    int month;
    int day;
    int result;

    result = scanf("%d %d %d", &year, &month, &day);
    if (result != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_valid_gregorian_date(year, month, day)) {
        puts("Valid date");
        return EXIT_SUCCESS;
    }

    puts("Invalid date");
    return EXIT_FAILURE;
}