#include <stdio.h>
#include <stdbool.h>

bool isValidDate(int day, int month, int year) {
    if (year < 1 || year > 9999 || month < 1 || month > 12) 
        return false;
    if (day < 1 || day > 31) 
        return false;

    if (month == 2) {
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
            if (day > 29) 
                return false;
        } else {
            if (day > 28) 
                return false;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) 
            return false;
    }

    return true;
}

int main() {
    int day, month, year;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);

    if (isValidDate(day, month, year)) {
        printf("Date is valid.\n");
    } else {
        printf("Date is not valid.\n");
    }

    return 0;
}