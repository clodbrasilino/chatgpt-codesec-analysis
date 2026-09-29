#include <stdio.h>
#include <stdbool.h>

bool has_30_days(int month) {
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void) {
    int months[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, -1};
    int num_months = sizeof(months) / sizeof(months[0]);
    
    for (int i = 0; i < num_months; i++) {
        printf("Month %d: %s\n", months[i], has_30_days(months[i]) ? "has 30 days" : "does not have 30 days");
    }
    
    return 0;
}