#include <stdio.h>
#include <stdbool.h>

bool has_28_days(int month)
{
    return (month == 2);
}

int main(void)
{
    int month;
    
    if (printf("Enter month number (1-12): ") < 0) {
        return 1;
    }
    
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (month < 1 || month > 12) {
        fprintf(stderr, "Month must be between 1 and 12\n");
        return 1;
    }
    
    if (has_28_days(month)) {
        printf("Month %d contains 28 days\n", month);
    } else {
        printf("Month %d does not contain 28 days\n", month);
    }
    
    return 0;
}