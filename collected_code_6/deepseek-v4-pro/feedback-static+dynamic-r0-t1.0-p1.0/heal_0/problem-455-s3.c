#include <stdio.h>

int has_31_days(int month) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 1;
        case 4:
        case 6:
        case 9:
        case 11:
            return 0;
        default:
            return -1;
    }
}

int main(void) {
    int month;
    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    int result = has_31_days(month);
    if (result == 1) {
        printf("Month %d has 31 days\n", month);
    } else if (result == 0) {
        printf("Month %d does not have 31 days\n", month);
    } else {
        printf("Invalid month number\n");
    }

    return 0;
}