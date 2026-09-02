#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool is_valid_date(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1) {
        return false;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (is_leap_year(year)) {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1]) {
        return false;
    }

    return true;
}

int main() {
    int day, month, year;

    printf("Enter date (day month year): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (is_valid_date(day, month, year)) {
        printf("The date is valid.\n");
    } else {
        printf("The date is invalid.\n");
    }

    return 0;
}