#include <stdio.h>
#include <stdlib.h>

int has_28_days(int month) {
    if (month < 1 || month > 12) {
        return 0;
    }
    return (month == 2) ? 1 : 0;
}

int main(void) {
    int month;
    int result;

    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return EXIT_FAILURE;
    }

    result = has_28_days(month);

    if (result) {
        printf("Month %d has 28 days (or 29 in leap years).\n", month);
    } else {
        if (month >= 1 && month <= 12) {
            printf("Month %d does not have exactly 28 days.\n", month);
        } else {
            printf("Invalid month number.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}