#include <stdio.h>
#include <stdbool.h>

bool has_28_days(int month) {
    return month == 2;
}

int main() {
    int month;
    printf("Enter a month number (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input. Please enter a number between 1 and 12.\n");
        return 1;
    }
    if (has_28_days(month)) {
        printf("The given month contains 28 days.\n");
    } else {
        printf("The given month does not contain 28 days.\n");
    }
    return 0;
}