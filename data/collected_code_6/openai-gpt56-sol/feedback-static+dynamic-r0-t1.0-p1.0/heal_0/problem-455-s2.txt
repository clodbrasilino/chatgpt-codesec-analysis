#include <stdio.h>
#include <stdlib.h>

static int has_31_days(int month)
{
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 1;
        default:
            return 0;
    }
}

int main(void)
{
    int month;

    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Month must be between 1 and 12.\n");
        return EXIT_FAILURE;
    }

    printf("Month %d %s 31 days.\n",
           month, has_31_days(month) ? "contains" : "does not contain");

    return EXIT_SUCCESS;
}