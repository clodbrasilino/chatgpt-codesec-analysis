#include <stdio.h>
#include <string.h>

#define MAX_MONTH_LENGTH 20

int checkDays(const char *month) {
    if(strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 || strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 || strcmp(month, "December") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    char month[MAX_MONTH_LENGTH] = "";

    printf("Enter month name: ");
    fgets(month, MAX_MONTH_LENGTH, stdin);

    // Remove trailing newline
    month[strcspn(month, "\n")] = 0;

    if(checkDays(month)) {
        printf("%s has 31 days.\n", month);
    }
    else {
        printf("%s does not have 31 days.\n", month);
    }
    return 0;
}