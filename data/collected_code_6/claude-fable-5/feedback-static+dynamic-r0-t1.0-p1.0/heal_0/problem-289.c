#include <stdio.h>
#include <stdlib.h>

int calculateOddDays(int year);

int calculateOddDays(int year)
{
    int leapYears;
    int ordinaryYears;
    int totalOddDays;

    leapYears = (year / 4) - (year / 100) + (year / 400);
    ordinaryYears = year - leapYears;
    totalOddDays = ((ordinaryYears % 7) + ((leapYears * 2) % 7)) % 7;

    return totalOddDays;
}

int main(void)
{
    int year;
    int oddDays;
    int result;

    printf("Enter a year: ");
    result = scanf("%d", &year);

    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (year < 0)
    {
        fprintf(stderr, "Error: year must be non-negative.\n");
        return EXIT_FAILURE;
    }

    oddDays = calculateOddDays(year);
    printf("Number of odd days in year %d: %d\n", year, oddDays);

    return EXIT_SUCCESS;
}