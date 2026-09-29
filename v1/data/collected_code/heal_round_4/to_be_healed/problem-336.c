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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MAX_MONTH_LENGTH + 2];
    printf("Enter month name: ");
    if (!fgets(month, sizeof(month), stdin)) {
        printf("Error reading the input!\n");
        return 1;
    }
    month[strcspn(month, "\n")] = 0;

    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid input!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }
    return 0;
}