#include <stdio.h>

int has_30_days(int month)
{
    return (month == 4 || month == 6 || month == 9 || month == 11);
}

int main(void)
{
    int month;

    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (month < 1 || month > 12)
    {
        fprintf(stderr, "Month must be between 1 and 12\n");
        return 1;
    }

    if (has_30_days(month))
    {
        printf("Month %d has 30 days\n", month);
    }
    else
    {
        printf("Month %d does not have 30 days\n", month);
    }

    return 0;
}