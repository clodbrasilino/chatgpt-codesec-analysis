#include <stdio.h>
#include <stdbool.h>

static bool month_has_31_days(int month)
{
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return true;
        default:
            return false;
    }
}

int main(void)
{
    int month;

    printf("Enter month number (1-12): ");

    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Month must be between 1 and 12.\n");
        return 1;
    }

    printf("%s\n", month_has_31_days(month) ? "Yes" : "No");

    return 0;
}