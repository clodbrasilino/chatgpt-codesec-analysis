#include <stdio.h>
#include <stdbool.h>

bool is_leap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool is_valid_date(int day, int month, int year) {
    if (year < 1583) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    /* Possible weaknesses found:
     *  Variable 'days_in_month' can be declared as const array [constVariable]
     */
    int days_in_month[] = {31, 28 + is_leap(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day > days_in_month[month - 1]) return false;

    return true;
}

int main() {
    int day, month, year;

    printf("Enter the date (DD MM YYYY): ");
    if (scanf("%d %d %d", &day, &month, &year) != 3) {
        printf("Invalid input format.\n");
        return 1;
    }

    if (is_valid_date(day, month, year)) {
        printf("The date is valid.\n");
    } else {
        printf("The date is invalid.\n");
    }

    return 0;
}