#include <stdio.h>
#include <string.h>

int checkMonthDays(char *month) {
    /* Possible weaknesses found:
     *  Cannot determine that 'month[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
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
    char month[20];
    printf("Enter the month name: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'month[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
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