#include <stdio.h>
#include <stdbool.h>

bool has_28_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    return month == 2;
}

int main(void) {
    int months[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 13, -5};
    int num_tests = sizeof(months) / sizeof(months[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Month %d: %s\n", months[i], 
               has_28_days(months[i]) ? "has 28 days" : "does not have 28 days");
    }
    
    return 0;
}