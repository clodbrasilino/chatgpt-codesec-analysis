#include <stdio.h>

int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

int odd_days_in_year(int year) {
    int days = is_leap_year(year) ? 366 : 365;
    return days % 7;
}

int main() {
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    int odd_days = odd_days_in_year(year);
    printf("Number of odd days in %d: %d\n", year, odd_days);
    return 0;
}