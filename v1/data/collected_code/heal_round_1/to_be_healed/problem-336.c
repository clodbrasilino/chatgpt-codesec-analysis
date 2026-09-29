#include <stdio.h>
#include <string.h>

int checkMonthDays(char monthName[]) {
    int days = -1;
    /* Possible weaknesses found:
     *  Cannot determine that 'monthName[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (strcmp(monthName, "February") == 0 || strcmp(monthName, "february") == 0) {
        days = 28;
    }
    return days;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[20];
    printf("Enter month name: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'month[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", month);
    int days = checkMonthDays(month);
    if (days == -1) {
        printf("Invalid input!\n");
    } else {
        printf("Number of days in %s: %d\n", month, days);
    }
    return 0;
}