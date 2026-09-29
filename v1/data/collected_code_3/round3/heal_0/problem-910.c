#include <stdio.h>
#include <stdbool.h>

bool isValidDate(int day, int month, int year) {
    if (year < 1800 || year > 9999 || month < 1 || month > 12)
        return false;

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap)
            daysInMonth[month] = 29;
    }

    return day > 0 && day <= daysInMonth[month];
}

int main() {
    int day, month, year;

    printf("Enter date (dd mm yyyy): ");
    scanf("%d %d %d", &day, &month, &year);

    if (isValidDate(day, month, year))
        printf("The date is valid.\n");
    else
        printf("The date is not valid.\n");

    return 0;
}