#include <stdio.h>
#include <string.h>

int checkMonthDays(char monthName[]) {
    int days = -1;
    if (strcmp(monthName, "February") == 0 || strcmp(monthName, "february") == 0) {
        days = 28;
    }
    return days;
}

int main() {
    char month[20];
    printf("Enter month name: ");
    scanf("%s", month);
    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid input!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }
    return 0;
}