#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    if (year < 1) {
        return false;
    }
    if (year % 4 != 0) {
        return false;
    }
    if (year % 100 != 0) {
        return true;
    }
    if (year % 400 == 0) {
        return true;
    }
    return false;
}

int calculate_odd_days(int year) {
    if (year < 1) {
        return -1;
    }
    int odd_days = year % 400;
    int centuries = odd_days / 100;
    int remaining_years = odd_days % 100;
    int leap_years = remaining_years / 4;
    int ordinary_years = remaining_years - leap_years;
    return (centuries * 5 + leap_years * 2 + ordinary_years) % 7;
}

int main() {
    int year = 2023;
    int result = calculate_odd_days(year);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}