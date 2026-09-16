#include <stdio.h>

int is_leap_year(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int odd_days_in_year(int year) {
    int days = 365 + is_leap_year(year);
    return days % 7;
}

int main() {
    int year;
    printf("Enter a year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int odd_days = odd_days_in_year(year);
    printf("Number of odd days in %d: %d\n", year, odd_days);
    return 0;
}