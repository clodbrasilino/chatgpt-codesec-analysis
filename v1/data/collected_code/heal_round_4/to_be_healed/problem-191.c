#include <stdio.h>
#include <string.h>

#define MONTH_MAX_LENGTH 20

int checkMonthDays(const char *month) {
    if (strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 ||
        strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 ||
        strcmp(month, "December") == 0) {
        return 31;
    } else if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || strcmp(month, "September") == 0 ||
               strcmp(month, "November") == 0) {
        return 30;
    } else {
        return -1;
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MONTH_MAX_LENGTH+1];
    printf("Enter the month name: ");
    fgets(month, sizeof(month), stdin);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if ((strlen(month) > 0) && (month[strlen (month) - 1] == '\n'))
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        month[strlen (month) - 1] = '\0';
      
    int days = checkMonthDays(month);

    if (days == 31) {
        printf("The month %s has 31 days. \n", month);
    } else if (days == 30) {
        printf("The month %s has 30 days. \n", month);
    } else {
        printf("Invalid month name. \n");
    }

    return 0;
}