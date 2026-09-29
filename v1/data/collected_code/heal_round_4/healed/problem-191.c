#include <stdio.h>
#include <string.h>

#define MONTH_MAX_LENGTH 20

int checkMonthDays(const char *month) {
    if (strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0  ||
        strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 ||
        strcmp(month, "December") == 0) {
        return 31;
    } else if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || 
               strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return 30;
    } else {
        return -1;
    }
}

int main() {
    char month[MONTH_MAX_LENGTH+1] = {0};
    printf("Enter the month name: ");
    fgets(month, sizeof(month), stdin);
    size_t monthLen = strlen(month);
    if (monthLen > 0 && month[monthLen - 1] == '\n') {
        month[monthLen - 1] = '\0';
    }
  
    int days = checkMonthDays(month);
    if (days == 31) {
        printf("The month %s has 31 days.\n", month);
    } else if (days == 30) {
        printf("The month %s has 30 days.\n", month);
    } else {
        printf("Invalid month name.\n");
    }
    
    return 0;
}