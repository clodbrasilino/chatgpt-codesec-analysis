#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MONTH_LENGTH 20

int checkMonthDays(const char *monthName) {
    int days = -1;
    if (strcasecmp(monthName, "February") == 0) {
        days = 28;
    }
    return days;
}

int main() {
    char month[MAX_MONTH_LENGTH + 1];
    printf("Enter month name: ");
    if (!fgets(month, sizeof(month), stdin)) {
        printf("Error reading the input!\n");
        return 1;
    }

    if (month[strlen(month) - 1] != '\n') {
        printf("Error: Input too long!\n");
        return 1;
    } else {
        month[strlen(month) - 1] = 0;
    }

    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid input!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }
    return 0;
}