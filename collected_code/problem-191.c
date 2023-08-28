#include <stdio.h>
#include <string.h>

int checkMonthDays(char *month) {
    if (strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 ||
        strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 ||
        strcmp(month, "December") == 0) {
        return 1;
    } else if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || strcmp(month, "September") == 0 ||
               strcmp(month, "November") == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    char month[20];
    printf("Enter the month name: ");
    scanf("%s", month);

    int result = checkMonthDays(month);

    if (result == 1) {
        printf("The month %s contains 30 days. \n", month);
    } else if (result == 0) {
        printf("The month %s does not contain 30 days. \n", month);
    } else {
        printf("Invalid month name. \n");
    }

    return 0;
}