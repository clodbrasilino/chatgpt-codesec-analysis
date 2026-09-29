#include <stdio.h>
#include <string.h>

#define MAX_MONTH_LENGTH 20

int checkMonthDays(const char *monthName) {
    int days = -1;
    if (strcasecmp(monthName, "February") == 0) {
        days = 28;
    }
    return days;
}

int main() {
    char month[MAX_MONTH_LENGTH];
    printf("Enter month name: ");
    scanf("%19s", month);
    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid input!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }
    return 0;
}