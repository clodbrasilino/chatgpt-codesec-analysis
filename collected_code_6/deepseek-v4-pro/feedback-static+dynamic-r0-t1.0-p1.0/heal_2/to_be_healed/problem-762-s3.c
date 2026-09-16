#include <stdio.h>

int has_30_days(int month) {
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'month=4', assigned value is 4
     */
    int month = 4;
    /* Possible weaknesses found:
     *  Condition 'has_30_days(month)' is always true [knownConditionTrueFalse]
     *  Calling function 'has_30_days' returns 1
     *  Condition 'has_30_days(month)' is always true
     */
    if (has_30_days(month)) {
        printf("Month %d has 30 days.\n", month);
    } else {
        printf("Month %d does not have 30 days.\n", month);
    }
    return 0;
}