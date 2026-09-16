#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool is_leap_year(int year) {
    if (year % 4 != 0) {
        return false;
    }
    if (year % 100 != 0) {
        return true;
    }
    if (year % 400 != 0) {
        return false;
    }
    return true;
}

bool validate_gregorian_date(int day, int month, int year) {
    if (year < 1582) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1) {
        return false;
    }

    int max_days;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        max_days = 30;
    } else if (month == 2) {
        if (is_leap_year(year)) {
            max_days = 29;
        } else {
            max_days = 28;
        }
    } else {
        max_days = 31;
    }

    if (day > max_days) {
        return false;
    }

    if (year == 1582 && month == 10 && day < 15) {
        return false;
    }

    return true;
}

int main(void) {
    int day;
    int month;
    int year;

    if (scanf("%d %d %d", &year, &month, &day) != 3) {
        return 1;
    }

    if (validate_gregorian_date(day, month, year)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }

    return 0;
}