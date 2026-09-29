#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool has_28_days(int month)
{
    return (month == 2);
}

int main(void)
{
    int month = 0;
    int result = 0;

    printf("Enter month number (1-12): ");
    result = scanf("%d", &month);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if ((month < 1) || (month > 12)) {
        fprintf(stderr, "Error: month must be between 1 and 12.\n");
        return EXIT_FAILURE;
    }

    if (has_28_days(month)) {
        printf("Month %d contains 28 days.\n", month);
    } else {
        printf("Month %d does not contain 28 days.\n", month);
    }

    return EXIT_SUCCESS;
}