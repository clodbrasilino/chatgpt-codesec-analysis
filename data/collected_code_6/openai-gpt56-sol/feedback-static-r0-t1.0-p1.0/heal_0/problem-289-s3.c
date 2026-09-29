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

    if (scanf("%d", &year) != 1 || year < 1) {
        fprintf(stderr, "Invalid year\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", odd_days_in_year(year));
    return EXIT_SUCCESS;
}