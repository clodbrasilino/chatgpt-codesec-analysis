#include <stdio.h>

int has_28_days(int month) {
    if (month < 1 || month > 12) {
        return 0;
    }
    return month == 2;
}

int main(void) {
    int month;
    
    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (has_28_days(month)) {
        printf("Month %d has 28 days\n", month);
    } else {
        printf("Month %d does not have 28 days\n", month);
    }
    
    return 0;
}