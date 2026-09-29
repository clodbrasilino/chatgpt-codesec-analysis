#include <stdio.h>
#include <stdbool.h>

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 1 || year > 9999 || month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 2) {
        if (isLeap(year))
            return (day <= 29);
        else
            return (day <= 28);
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);

    return true;
}

int main() {
    int day, month, year;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);

    if (isValidDate(day, month, year))
        printf("The date is valid.\n");
    else
        printf("The date is not valid.\n");

    return 0;
}