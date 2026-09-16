#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
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
    
    if (has_31_days(month)) {
        printf("Month %d has 31 days\n", month);
    } else {
        printf("Month %d does not have 31 days\n", month);
    }
    
    return 0;
}