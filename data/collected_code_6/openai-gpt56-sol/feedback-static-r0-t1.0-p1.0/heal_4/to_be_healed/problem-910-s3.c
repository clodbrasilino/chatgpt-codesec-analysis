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

    if (year < 1582 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    maximum_day = days_per_month[month - 1];

    if (month == 2 && is_leap_year(year)) {
        maximum_day = 29;
    }

    return day <= maximum_day;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *const argv[const])
{
    int year;
    int month;
    int day;
    char trailing;

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (scanf("%d %d %d %c", &year, &month, &day, &trailing) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_gregorian_date(year, month, day)) {
        puts("Invalid date");
        return EXIT_FAILURE;
    }

    puts("Valid date");
    return EXIT_SUCCESS;
}