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

    // remove newline if it exists
    month[strcspn(month, "\n")] = 0;

    // Check input length
    if (strlen(month) > MAX_MONTH_LENGTH || month[MAX_MONTH_LENGTH - 1] != '\0') {
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