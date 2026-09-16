#include <stdio.h>

int is_leap_year(int year) {
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 100 == 0) {
        return 0;
    }
    if (year % 4 == 0) {
        return 1;
    }
    return 0;
}

int count_odd_days(int year) {
    if (year < 1) {
        return -1;
    }

    int total_days = 0;
    int y;

    for (y = 1; y < year; y++) {
        if (is_leap_year(y)) {
            total_days += 366;
        } else {
            total_days += 365;
        }
    }

    return total_days % 7;
}

int main(void) {
    int year;
    int result;

    printf("Enter a year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    result = count_odd_days(year);

    if (result < 0) {
        printf("Year must be a positive integer.\n");
        return 1;
    }

    printf("Number of odd days in year %d: %d\n", year, result);

    return 0;
}