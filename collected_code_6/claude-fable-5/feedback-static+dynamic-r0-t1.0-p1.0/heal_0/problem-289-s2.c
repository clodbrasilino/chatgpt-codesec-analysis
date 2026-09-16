#include <stdio.h>
#include <stdlib.h>

static int is_leap_year(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

static int odd_days_in_year(int year)
{
    int total_days;

    if (is_leap_year(year))
    {
        total_days = 366;
    }
    else
    {
        total_days = 365;
    }

    return total_days % 7;
}

int main(void)
{
    int year = 0;
    int result;

    printf("Enter a year: ");

    if (scanf("%d", &year) != 1)
    {
        fprintf(stderr, "Error: invalid input, expected an integer.\n");
        return EXIT_FAILURE;
    }

    if (year < 1)
    {
        fprintf(stderr, "Error: year must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = odd_days_in_year(year);

    printf("Number of odd days in year %d: %d\n", year, result);

    return EXIT_SUCCESS;
}