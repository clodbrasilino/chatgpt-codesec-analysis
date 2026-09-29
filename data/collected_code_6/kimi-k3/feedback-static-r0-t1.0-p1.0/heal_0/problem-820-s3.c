#include <stdio.h>

int has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    int month;
    int result;

    printf("Enter month number (1-12): ");
    result = scanf("%d", &month);

    if (result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (month < 1 || month > 12)
    {
        fprintf(stderr, "Month must be between 1 and 12\n");
        return 1;
    }

    if (has_28_days(month))
    {
        printf("Month %d has 28 days\n", month);
    }
    else
    {
        printf("Month %d does not have 28 days\n", month);
    }

    return 0;
}