#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_thirty_days(int month)
{
    switch (month) {
    case 4:
    case 6:
    case 9:
    case 11:
        return true;
    default:
        return false;
    }
}

int main(void)
{
    int month = 0;

    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Error: month must be between 1 and 12.\n");
        return EXIT_FAILURE;
    }

    if (has_thirty_days(month)) {
        printf("Month %d has 30 days.\n", month);
    } else {
        printf("Month %d does not have 30 days.\n", month);
    }

    return EXIT_SUCCESS;
}