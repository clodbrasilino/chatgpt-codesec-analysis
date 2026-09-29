#include <stdio.h>

int is_thirty_days(int month)
{
    return (month == 4 || month == 6 || month == 9 || month == 11);
}

int main(void)
{
    int month = 0;
    int status = 0;
    int result = 0;

    status = scanf("%d", &month);
    if (status != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (month < 1 || month > 12)
    {
        fprintf(stderr, "Month out of range\n");
        return 1;
    }

    result = is_thirty_days(month);
    if (result)
    {
        printf("Month %d has 30 days\n", month);
    }
    else
    {
        printf("Month %d does not have 30 days\n", month);
    }

    return 0;
}