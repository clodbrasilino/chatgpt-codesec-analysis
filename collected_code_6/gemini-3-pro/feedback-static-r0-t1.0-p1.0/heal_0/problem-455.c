#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || 
        month == 8 || month == 10 || month == 12) {
        return true;
    }
    return false;
}

int main(void) {
    int month;

    if (scanf("%d", &month) != 1) {
        return 1;
    }

    if (month < 1 || month > 12) {
        return 1;
    }

    if (has_31_days(month)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}