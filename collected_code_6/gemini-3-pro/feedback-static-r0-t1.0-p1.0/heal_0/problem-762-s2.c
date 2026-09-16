#include <stdio.h>
#include <stdbool.h>

bool has_30_days(int month) {
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return true;
    }
    return false;
}

int main(void) {
    int month;
    int result;

    printf("Enter month number (1-12): ");
    result = scanf("%d", &month);

    if (result != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (month < 1 || month > 12) {
        printf("Month must be between 1 and 12.\n");
        return 1;
    }

    if (has_30_days(month)) {
        printf("Month %d has 30 days.\n", month);
    } else {
        printf("Month %d does not have exactly 30 days.\n", month);
    }

    return 0;
}