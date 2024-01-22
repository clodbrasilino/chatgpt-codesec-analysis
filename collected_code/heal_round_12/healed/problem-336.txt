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
    char month[MAX_MONTH_LENGTH + 1] = {0};

    printf("Enter month name: ");
    
    if (fgets(month, sizeof(month), stdin) == NULL) {
        printf("Error reading the input!\n");
        return 1;
    }

    size_t len = strcspn(month, "\n");
    month[len] = '\0';

    if (len > MAX_MONTH_LENGTH || len != strlen(month)) {
        printf("Input too long or not properly terminated!\n");
        return 1;
    }

    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid month name!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }

    return 0;
}