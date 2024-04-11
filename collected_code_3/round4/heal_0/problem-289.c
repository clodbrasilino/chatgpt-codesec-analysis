#include <stdio.h>

int countOddDays(int year) {
    int days = 0;
    for(int month = 1; month <= 12; month++) {
        int monthDays = 0;
        if(month == 2) {
            if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                monthDays = 29;
            } else {
                monthDays = 28;
            }
        } else if(month == 4 || month == 6 || month == 9 || month == 11) {
            monthDays = 30;
        } else {
            monthDays = 31;
        }
        for(int day = 1; day <= monthDays; day++) {
            if(day % 2 != 0) {
                days++;
            }
        }
    }
    return days;
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    printf("Number of odd days in year %d is %d\n", year, countOddDays(year));
    return 0;
}