#include <stdio.h>
#include <stdbool.h>

bool has_30_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void) {
    int month;
    if (scanf("%d", &month) != 1) {
        return 1;
    }
    if (has_30_days(month)) {
        printf("Contains 30 days\n");
    } else {
        printf("Does not contain 30 days\n");
    }
    return 0;
}