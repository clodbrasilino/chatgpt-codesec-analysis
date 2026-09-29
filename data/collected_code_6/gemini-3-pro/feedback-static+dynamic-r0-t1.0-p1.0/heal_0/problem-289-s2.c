#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    if (year % 4 == 0) {
        return true;
    }
    return false;
}

int calculate_odd_days(int year) {
    if (year < 1) {
        return -1;
    }

    year = year - 1;
    int odd_days = year % 400;
    
    int days = 0;
    days += (odd_days / 100) * 5;
    odd_days %= 100;

    int leap_years = odd_days / 4;
    int ordinary_years = odd_days - leap_years;

    days += (leap_years * 2) + ordinary_years;
    days %= 7;

    return days;
}

int main(void) {
    int year;
    int result;

    if (scanf("%d", &year) != 1) {
        return 1;
    }

    result = calculate_odd_days(year);
    if (result == -1) {
        return 1;
    }

    printf("%d\n", result);

    return 0;
}