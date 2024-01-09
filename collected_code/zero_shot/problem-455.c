#include <stdio.h>

int check31Days(int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int month;
    printf("Enter month number: ");
    scanf("%d", &month);
    
    if (check31Days(month)) {
        printf("The month number %d contains 31 days.\n", month);
    } else {
        printf("The month number %d does not contain 31 days.\n", month);
    }
    
    return 0;
}