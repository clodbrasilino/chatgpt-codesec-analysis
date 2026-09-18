#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isValidDate(int day, int month, int year) {
    
    if (year < 1800 || year > 9999)
        return false;

    if (month < 1 || month > 12)
        return false;
    
    if (day < 1 || day > 31)
        return false;
    
    if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            if(day > 29)
                return false;
        } else {
            if(day > 28)
                return false;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if(day > 30)
            return false;
    }

    return true;
}


int main(void) {
    int day, month, year;
    
    printf("Enter date (DD MM YYYY) : ");
    scanf("%d %d %d", &day, &month, &year);
    
    if(isValidDate(day, month, year)) {
        printf("Valid date\n");
    } else {
        printf("Invalid date\n");
    }
    
    return 0;
} 