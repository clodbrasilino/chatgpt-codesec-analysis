#include <stdio.h>
#include <stdlib.h>

static int has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    int month;
    int result;

    printf("Enter month number: ");

    result = scanf("%d", &month);
    if (result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Month number must be between 1 and 12.\n");
        return EXIT_FAILURE;
    }

    if (has_28_days(month)) {
        printf("The month contains 28 days.\n");
    } else {
        printf("The month does not contain 28 days.\n");
    }

    return EXIT_SUCCESS;
}