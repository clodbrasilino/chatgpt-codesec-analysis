#include <stdio.h>

int has_30_days(int month) {
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void) {
    int month = 4;
    if (has_30_days(month)) {
        printf("Month %d has 30 days.\n", month);
    } else {
        printf("Month %d does not have 30 days.\n", month);
    }
    return 0;
}