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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MAX_MONTH_LENGTH] = "";
    char *newline = NULL;

    printf("Enter month name: ");
    if (fgets(month, MAX_MONTH_LENGTH, stdin) != NULL) {
        newline = strchr(month, '\n');
        if (newline) {
            *newline = '\0';
        }
        if (checkDays(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }
    return 0;
}