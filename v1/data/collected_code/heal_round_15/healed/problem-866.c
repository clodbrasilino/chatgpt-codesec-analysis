#include <stdio.h>
#include <string.h>

#define MAX_MONTH_LENGTH 22

int checkDays(const char *month) {
    const char *longMonths[] = { "January", "March", "May", "July", "August", "October", "December" };
    size_t longMonthsCount = sizeof(longMonths) / sizeof(longMonths[0]);
    for (size_t i = 0; i < longMonthsCount; ++i) {
        if (strcmp(month, longMonths[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char month[MAX_MONTH_LENGTH] = "";
    char *newline = NULL;

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        newline = strchr(month, '\n');
        if (newline) {
            *newline = '\0';
        }

        if (strlen(month) < MAX_MONTH_LENGTH) {
            if (checkDays(month)) {
                printf("%s has 31 days.\n", month);
            } else {
                printf("%s does not have 31 days.\n", month);
            }
        } else {
           printf("Month name too long.\n");
        }
    }
    return 0;
}