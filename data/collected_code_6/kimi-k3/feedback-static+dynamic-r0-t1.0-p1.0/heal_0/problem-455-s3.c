#include <stdio.h>

int has_31_days(int month) {
    if (month < 1 || month > 12) {
        return 0;
    }
    return (month == 1 || month == 3 || month == 5 || month == 7 ||
            month == 8 || month == 10 || month == 12);
}

int main(void) {
    int month;
    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (has_31_days(month)) {
        printf("Month %d has 31 days\n", month);
    } else {
        printf("Month %d does not have 31 days\n", month);
    }
    return 0;
}