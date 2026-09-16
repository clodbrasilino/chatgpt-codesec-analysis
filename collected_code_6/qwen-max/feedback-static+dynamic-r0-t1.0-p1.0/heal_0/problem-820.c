#include <stdio.h>
#include <stdbool.h>

bool has28Days(int month) {
    return (month == 2);
}

int main() {
    int month;
    printf("Enter the month number (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid input. Please enter a valid month number.\n");
        return 1;
    }
    if (has28Days(month)) {
        printf("The given month contains 28 days.\n");
    } else {
        printf("The given month does not necessarily contain 28 days.\n");
    }
    return 0;
}