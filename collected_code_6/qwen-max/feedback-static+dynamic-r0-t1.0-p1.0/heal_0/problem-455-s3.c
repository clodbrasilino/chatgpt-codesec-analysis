#include <stdio.h>
#include <stdbool.h>

bool has_31_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    return month == 1 || month == 3 || month == 5 || month == 7 ||
           month == 8 || month == 10 || month == 12;
}

int main() {
    int month;
    printf("Enter the month number (1-12): ");
    scanf("%d", &month);
    if (has_31_days(month)) {
        printf("The month has 31 days.\n");
    } else {
        printf("The month does not have 31 days.\n");
    }
    return 0;
}