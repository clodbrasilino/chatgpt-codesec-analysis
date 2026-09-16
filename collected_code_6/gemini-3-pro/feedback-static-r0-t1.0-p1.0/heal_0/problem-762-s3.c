#include <stdio.h>
#include <stdbool.h>

bool has_30_days(int month) {
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return true;
    }
    return false;
}

int main(void) {
    int month = 0;
    
    if (scanf("%d", &month) != 1) {
        return 1;
    }
    
    if (month < 1 || month > 12) {
        return 1;
    }
    
    if (has_30_days(month)) {
        printf("The month has 30 days.\n");
    } else {
        printf("The month does not have 30 days.\n");
    }
    
    return 0;
}