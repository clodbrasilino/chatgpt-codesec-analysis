#include <stdio.h>
#include <string.h>

#define MAX_MONTH_LENGTH 21

int checkDays(const char *month) {
    if(strcmp(month, "January") == 0 || strcmp(month, "March") == 0 || strcmp(month, "May") == 0 || strcmp(month, "July") == 0 || strcmp(month, "August") == 0 || strcmp(month, "October") == 0 || strcmp(month, "December") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MAX_MONTH_LENGTH] = "";
    printf("Enter month name: ");
    if (fgets(month, MAX_MONTH_LENGTH, stdin) != NULL) {
        month[strcspn(month, "\n")] = 0;
        if(checkDays(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}