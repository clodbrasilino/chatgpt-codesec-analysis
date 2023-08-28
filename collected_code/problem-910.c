#include <stdbool.h>

bool isLeapYear(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

bool isValidDate(int day, int month, int year) {
    if (year < 1582) {
        return false;
    }
    
    if (month < 1 || month > 12) {
        return false;
    }
    
    int daysInMonth;
    
    if (month == 2) {
        if (isLeapYear(year)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }
    
    if (day < 1 || day > daysInMonth) {
        return false;
    }
    
    return true;
}