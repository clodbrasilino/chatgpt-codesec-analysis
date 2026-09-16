#include <stdio.h>
#include <stdlib.h>

int contains_28_days(int month) {
    if (month >= 1 && month <= 12) {
        if (month == 2) {
            return 1;
        }
        return 0;
    }
    return -1;
}

int main(void) {
    int month;
    int result;

    if (scanf("%d", &month) != 1) {
        return EXIT_FAILURE;
    }

    result = contains_28_days(month);

    if (result == 1) {
        printf("Month %d contains 28 days.\n", month);
    } else if (result == 0) {
        printf("Month %d does not contain exactly 28 days.\n", month);
    } else {
        printf("Invalid month.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}