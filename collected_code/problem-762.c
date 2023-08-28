#include <stdio.h>

int isThirtyDays(int month) {
    if (month < 1 || month > 12) {
        return 0;
    }
    
    int thirtyDays[] = {4, 6, 9, 11};
    
    for (int i = 0; i < 4; i++) {
        if (month == thirtyDays[i]) {
            return 1;
        }
    }
    
    return 0;
}

int main() {
    int month;
    
    printf("Enter a month number: ");
    scanf("%d", &month);
    
    if (isThirtyDays(month)) {
        printf("The given month number contains 30 days.\n");
    } else {
        printf("The given month number does not contain 30 days.\n");
    }
    
    return 0;
}