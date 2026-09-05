#include <stdio.h>
#include <stdlib.h>

int has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    int month;
    int result;

    if (printf("Enter month number (1-12): ") < 0) {
        fprintf(stderr, "Error writing output\n");
        return EXIT_FAILURE;
    }

    result = scanf("%d", &month);
    if (result != 1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Invalid month number\n");
        return EXIT_FAILURE;
    }

    if (has_28_days(month)) {
        if (printf("Month %d has 28 days.\n", month) < 0) {
            fprintf(stderr, "Error writing output\n");
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Month %d does not have 28 days.\n", month) < 0) {
            fprintf(stderr, "Error writing output\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}