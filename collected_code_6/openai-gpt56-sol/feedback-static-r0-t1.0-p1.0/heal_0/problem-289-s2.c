#include <stdio.h>
#include <stdlib.h>

static int is_leap_year(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

static int odd_days_in_year(int year)
{
    return is_leap_year(year) ? 2 : 1;
}

int main(void)
{
    int year;

    if (printf("Enter a year: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &year) != 1 || year <= 0) {
        fprintf(stderr, "Invalid year\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of odd days: %d\n", odd_days_in_year(year)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}