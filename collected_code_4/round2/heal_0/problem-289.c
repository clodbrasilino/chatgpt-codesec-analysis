#include <stdio.h>
#include <stdbool.h>

bool isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    } 
    else if (year % 100 == 0) {
        return false;
    } 
    else if (year % 4 == 0) {
        return true;
    } 
    else {
        return false;
    }
}

int countOddDays(int year) {
    if (isLeapYear(year)) {
        return 366 / 2;
    } else {
        return 365 / 2;
    }
}

int main() {
    int year;
    scanf("%d", &year);
    int oddDays = countOddDays(year);
    printf("Number of odd days in year %d is %d\n", year, oddDays);
    return 0;
}