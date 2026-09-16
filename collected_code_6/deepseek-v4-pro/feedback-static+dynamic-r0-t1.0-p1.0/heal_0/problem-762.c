#include <stdio.h>
#include <stdbool.h>

bool hasThirtyDays(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return true;
        default:
            return false;
    }
}

int main(void) {
    int month;
    
    printf("Enter month number (1-12): ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (month < 1 || month > 12) {
        printf("Invalid month number\n");
        return 1;
    }
    
    if (hasThirtyDays(month)) {
        printf("Month %d has 30 days\n", month);
    } else {
        printf("Month %d does not have 30 days\n", month);
    }
    
    return 0;
}