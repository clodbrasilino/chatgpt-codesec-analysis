#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    return month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12;
}

int main(void) {
    int month;
    if (scanf("%d", &month) == 1) {
        if (has_31_days(month)) {
            printf("%d\n", 1);
        } else {
            printf("%d\n", 0);
        }
    } else {
        printf("%d\n", 0);
    }
    return 0;
}