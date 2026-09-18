#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    if (year % 400 == 0) return true;
    else if ((year % 100 == 0) && (year % 400 != 0)) return false;
    else if (year % 4 == 0) return true;
    return false;
}

int odd_days_in_year(int year) {
    if (is_leap_year(year)) {
        return 366 / 2;
    }
    else {
        return 365 / 2;
    }
}

int main() {
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);
    
    int odd_days = odd_days_in_year(year);
    printf("Number of odd days in year %d: %d\n", year, odd_days);
    
    return 0;
}