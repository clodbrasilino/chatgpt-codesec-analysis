#include <stdio.h>
#include <string.h>

#define MAX_MONTH_LENGTH 22

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
    if (fgets(month, MAX_MONTH_LENGTH, stdin) != NULL) {
        month[strcspn(month, "\n")] = 0;
        if(month && strlen(month) < MAX_MONTH_LENGTH && checkDays(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }
    
    return 0;
}