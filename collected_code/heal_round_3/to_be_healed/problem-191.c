#include <stdio.h>
#include <string.h>

#define MONTH_MAX_LENGTH 20

int checkMonthDays(const char *month) {
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MONTH_MAX_LENGTH+1];
    printf("Enter the month name: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%20s", month);
    month[MONTH_MAX_LENGTH] = '\0';

    int result = checkMonthDays(month);

    if (result == 1) {
        printf("The month %s has 31 days. \n", month);
    } else if (result == 0) {
        printf("The month %s has 30 days. \n", month);
    } else {
        printf("Invalid month name. \n");
    }

    return 0;
}