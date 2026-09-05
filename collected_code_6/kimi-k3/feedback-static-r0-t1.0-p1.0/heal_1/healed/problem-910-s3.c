#include <stdio.h>
#include <stdbool.h>

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validate_date(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && is_leap_year(year)) {
        return day <= 29;
    }

    return day <= days_in_month[month - 1];
}

int main(void) {
    int year, month, day;

    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter month: ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter day: ");
    if (scanf("%d", &day) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (validate_date(year, month, day)) {
        printf("Valid date\n");
    } else {
        printf("Invalid date\n");
    }

    return 0;
}