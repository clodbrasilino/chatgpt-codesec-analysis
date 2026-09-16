#include <stdio.h>

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int odd_days_in_year(int year) {
    int days = is_leap_year(year) ? 366 : 365;
    return days % 7;
}

int main(void) {
    int year;
    int result;

    printf("Enter a year: ");
    result = scanf("%d", &year);

    if (result != 1 || year <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Odd days in year %d: %d\n", year, odd_days_in_year(year));

    return 0;
}